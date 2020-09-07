#include <cstdlib>
#include <vector>
#include <iostream>
#include "options.h"
#include "options++.h"

bool operator==(const custom_option& l, const custom_option& r) {
  return strcmp(l.long_name, r.long_name) == 0;
}

bool operator<(const custom_option& l, const custom_option& r) {
  return strcmp(l.long_name, r.long_name) < 0;
}

bool operator>(const custom_option& l, const custom_option& r) {
  return strcmp(l.long_name, r.long_name) > 0;
}

bool operator<=(const custom_option& l, const custom_option& r) {
  return strcmp(l.long_name, r.long_name) <= 0;
}

bool operator>=(const custom_option& l, const custom_option& r) {
  return strcmp(l.long_name, r.long_name) >= 0;
}

argument_parser::argument_parser(int ac, char* const* av, const std::vector<custom_option>& opts):
  argc(ac),
  argv(av)
{
  // Create options twomap from opts vector.
  for (size_t i = 0; i < opts.size(); i+=1) {
    options[i] = opts[i];
  }
  options_arr = NULL;
  help = false;
}

void argument_parser::cleanup() {
  delete[] options_arr;
}

argument_parser::~argument_parser() {
  cleanup();
}

void argument_parser::add_mutually_exclusive_groups(const std::vector<argument_group>& groups) {
  /* add_mutually_exclusive_groups adds a vector of mutually exclusive groups to the list of
     mutually exclusvie groups.
     
     The input, groups, must be a vector containing vectors of custom_options (argument_groups).
     The argument_groups are interpreted as mutually exclusive; including two options from different
     groups should be disallowed.
  */
  /* Convert the vector of argument_groups to a vector of vectors of size_t.     

     Each custom_option should be replaced in the new vector with its corresponding index in options.
     
     This must be done to create a vector that may be easily converted to a format compatible with
     options.c
  */
  std::vector<std::vector<size_t>> mutually_exclusive;
  mutually_exclusive.reserve(groups.size());
  for (const argument_group& group: groups) {
    std::vector<size_t> index_group;
    index_group.reserve(group.size());
    for (const custom_option& opt: group) {
      // Insert the custom_option index in place of the custom_option.
      auto find_result = options.find(opt);
      index_group.push_back(find_result->second);
    }
    mutually_exclusive.push_back(index_group);
  }
  exclusive_groups.push_back(mutually_exclusive);
}

void argument_parser::generate_options_arr() {
  // generate_options_arr creates an array from the values (T keys) of the options twomap.
  // This array is needed for compatibility with various functions in options.c.
  if (options_arr == NULL) {
    options_arr = new custom_option[options.size()];
    for (auto it = options.S_begin(); it != options.S_end(); ++it) {
      options_arr[it->first] = it->second;
    }
  }
}

void argument_parser::print_help() {
  // print_help prints a help message for the program using the arguments provided to the
  // argument_parser.
  // Generate the options_arr for use with options.c's print_help function.
  generate_options_arr();
  ::print_help(argv[0],options_arr,options.size());
}

std::unordered_map<std::string,std::variant<std::string,bool>> argument_parser::get_args() {
  // get_args parses arguments in argv using the custom_options given to the argument_parser.
  // Generate the options_arr for use with options.c's get_args, check_required, and exclude
  // functions.
  generate_options_arr();
  // Create arrays for use with options.c.
  bool* set = new bool[options.size()]();
  char** arguments = new char*[options.size()]();
  // Parse the arguments.
  ::get_args(argc,argv,options_arr,set,arguments,options.size());
  if (help) {
    // Check if the user wants help.
    auto help_result = options.T_find("help");
    if (help_result != options.T_end()) {
      if (set[help_result->second]) {
	// Print help message.
	print_help();
	delete[] set;
	delete[] arguments;
	cleanup();
	exit(help_code);
      }
    }
  }
  // Check for missing required arguments.
  int missing = check_required(set,options_arr,options.size());
  if (missing != ALL_REQUIRED_SET) {
    // Show error message and quit.
    required_error(&options_arr[missing]);
    delete[] set;
    delete[] arguments;
    cleanup();
    exit(1);
  }
  // Check exclusive groups.
  for (auto& mutually_exclusive: exclusive_groups) {
    // Create arrays based on mutually_exclusive for use with options.c's exclude.
    size_t** all_groups = new size_t*[mutually_exclusive.size()];
    size_t* group_sizes = new size_t[mutually_exclusive.size()];
    for (size_t i = 0; i < mutually_exclusive.size(); i+=1) {
      all_groups[i] = mutually_exclusive[i].data();
      group_sizes[i] = mutually_exclusive[i].size();
    }
    custom_option* conflict_a = NULL;
    custom_option* conflict_b = NULL;
    bool exclude_result = ::exclude(options_arr,
				    set,
				    (const size_t**)all_groups,
				    group_sizes,
				    mutually_exclusive.size(),
				    &conflict_a,
				    &conflict_b);
    if (exclude_result) {
      // Show error message with conflict and quit.
      exclude_error(conflict_a,conflict_b);
      cleanup();
      delete[] set;
      delete[] arguments;
      delete[] all_groups;
      delete[] group_sizes;
      exit(1);      
    }
    delete[] all_groups;
    delete[] group_sizes;
  }
  // Create argument map.
  std::unordered_map<std::string,std::variant<std::string,bool>> argmap;
  for (size_t arg_index = 0; arg_index < options.size(); arg_index+=1) {
    custom_option option = options[arg_index];
    if (set[arg_index]) {
      if (option.has_arg && (arguments[arg_index] != NULL)) {
	// Include the argument in the map.
	argmap[option.long_name] = std::string(arguments[arg_index]);
      }
      else {
	// The option was given without an argument, so simply set its value to true.
	argmap[option.long_name] = true;
      }
    }
  }
  delete[] set;
  delete[] arguments;
  return argmap;
}

void argument_parser::enable_help(unsigned int code=0) {
  // enable_help causes the argument_parser to automatically print a help message when an argument
  // named "help" is encountered.
  help = true;
  help_code = code;
}

void argument_parser::disable_help() {
  // disable_help prevents the argument_parser from automatically printing a help message when an
  // argument named "help" is encountered.
  help = false;
}
