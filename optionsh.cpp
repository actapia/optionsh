#include <nlohmann/json.hpp>
#include <iostream>
#include <variant>
#include <cstdlib>
#include <unordered_map>
#include "options/options++.h"
using json = nlohmann::json;

template<typename S,typename T>
std::variant<T,S> get_or_default(json& map,std::string key,S default_value) {
  auto iter = map.find(key);
  std::variant<T,S> var;
  if (iter != map.end()) {
    var = std::variant<T,S>(std::in_place_index<0>,iter.value().template get<T>());
  }
  else {
    var = std::variant<T,S>(std::in_place_index<1>,default_value);
  }
  return var;
}

template<typename S>
S get_or_default(json& map, std::string key, S default_value) {
  auto var = get_or_default<S,S>(map,key,default_value);
  try {
    return std::get<0>(var);
  }
  catch(const std::bad_variant_access& e) {
    return std::get<1>(var);
  }
}

const char* get_string_or_null(json& map,std::string key) {
  auto raw_value = get_or_default<const char*,std::string>(map,key,(const char*)NULL);
  if (std::holds_alternative<const char*>(raw_value)) {
    return std::get<const char*>(raw_value);
  }
  else {
    return strdup(std::get<std::string>(raw_value).c_str());
  }
  return NULL;
}


int main(int argc, char* argv[]) {
  std::cin >> std::noskipws;
  std::istream_iterator<char> cin_it(std::cin);
  std::istream_iterator<char> end;
  std::string json_in(cin_it, end);
  json options_json = json::parse(json_in);
  // for (auto v: j["options"]) {
  //   std::cout << v["long_name"].get<std::string>() << std::endl;
  // }
  std::vector<custom_option> options;
  std::unordered_map<std::string,custom_option> option_lookup;
  for (auto option: options_json["options"]) {
    custom_option arg = {strdup(option["long_name"].get<std::string>().c_str()),
    			 get_string_or_null(option,"short_name"),
    			 get_or_default<::argument_type>(option,"has_arg",POSITIONAL),
			 get_string_or_null(option,"help"),
    			 get_or_default<bool>(option,"optional",false
					      )};
    std::string key = std::string(arg.long_name);
    option_lookup[key] = arg;
    options.push_back(arg);			 
  }
  if (get_or_default<bool>(options_json,"help",false)) {
    if (!option_lookup.contains("help")) {
      custom_option arg = {strdup("help"),
			   NULL,
			   NO_ARGUMENT,
			   strdup("Show this help message."),
			   true};
      option_lookup["help"] = arg;
      options.push_back(arg);
			   
    }
  }
  for (int i = 0; i < argc-1; i++) {
    argv[i] = argv[i+1];
  }
  argument_parser parser(argc-1, argv, options);
  if (get_or_default<bool>(options_json,"help",false)) {
    parser.enable_help(101);
  }
  //std::vector<std::vector<argument_group>> group_vector;
  for (auto groups_json: options_json["groups"]) {
    std::vector<argument_group> groups;
    for (auto group_json: groups_json) {
      argument_group group;
      for (auto option_name: group_json) {
	group.push_back(option_lookup[option_name.get<std::string>()]);
      }
      groups.push_back(group);
    }
    parser.add_mutually_exclusive_groups(groups);
  }
  // Parse arguments.
  auto args = parser.get_args();
  // Print arguments.
  for (auto const& [arg, value]: args) {
    std::cout << arg << ":";
    if (std::holds_alternative<std::string>(value)) {
      std::cout << std::get<std::string>(value);
    }
    else {
      std::cout << std::boolalpha << std::get<bool>(value);
    }
    std::cout << std::endl;
  }
  // Cleanup.
  for (auto option: options) {
    free((char*)option.long_name);
    if (option.short_name != NULL) {
      free((char*)option.short_name);
    }
    if (option.help != NULL) {
      free((char*)option.help);
    }
  }
  return 0;
}

