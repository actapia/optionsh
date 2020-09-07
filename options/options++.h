#ifndef OPTIONSPP_H
#define OPTIONSPP_H

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include "options.h"
#include "../twomap/twomap.h"

// options++ provides a C++-style interface to the options.c argument parser I wrote for pa1.

typedef std::vector<custom_option> argument_group;

struct custom_option_search {
  // custom_option_search is a transparent comparator that allows searching for custom_options by
  // their long names in ordered associative containers.
  using is_transparent = void;
  bool operator()(custom_option const& l, custom_option const& r) const {
    return strcmp(l.long_name, r.long_name) < 0;
  }
  bool operator()(custom_option const& l, std::string const& r) const {
    return strcmp(l.long_name, r.c_str()) < 0;
  }
  bool operator()(std::string const& l, custom_option const& r) const {
    return strcmp(l.c_str(), r.long_name) < 0;
  }
};

class argument_parser {
  /* argument_parser is a class that provides (somewhat) object-oriented access to the features of the
     options.c argument parser.

     Like the options.c argument parser, this class was inspired (to some extent) by Python's
     argparse module.
  */
public:
  explicit argument_parser(int ac, char* const* av, const std::vector<custom_option>& options);
  void add_mutually_exclusive_groups(const std::vector<argument_group>& groups);
  std::unordered_map<std::string,std::variant<std::string,bool>> get_args();
  void print_help();
  void enable_help(unsigned int code);
  void disable_help();
  ~argument_parser();
private:
  // help is set to true when the argument_parser should print help automatically when an option named
  // "help" is provided.
  bool help;
  unsigned int help_code;
  int argc;
  char* const* argv;
  // options is a twomap between custom_options and their indices.
  // options allows both simulated access by index and fast lookup by name.
  twomap<size_t,custom_option,std::less<size_t>,custom_option_search> options;
  // exclusive_groups is a vector of vectors of vectors representing multiple mutually exclusive
  // groups of options.
  std::vector<std::vector<std::vector<size_t>>> exclusive_groups;
  // options_arr is an array created by some methods from options.
  // options_arr is stored to save time when multiple such methods are called.
  custom_option* options_arr;
  void cleanup();
  void generate_options_arr();
};

// These operators are needed to use custom_option in associative containers.
bool operator==(const custom_option& l, const custom_option& r);
bool operator<(const custom_option& l, const custom_option& r);
bool operator>(const custom_option& l, const custom_option& r);
bool operator<=(const custom_option& l, const custom_option& r);
bool operator>=(const custom_option& l, const custom_option& r);

#endif
