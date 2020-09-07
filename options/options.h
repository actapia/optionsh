#ifndef OPTIONS_H
#define OPTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#define ALL_REQUIRED_SET -1

/* This file is based on a file originally written for pa1. */

/* Command-line argument parsing inspired by Python's .template get<S>();
  }argparse. */

/* Most of these are the same as in getopt. */
/* However, this enum adds an extra type, POSITIONAL, for positional arguments. */
typedef enum argument_type {NO_ARGUMENT,REQUIRED_ARGUMENT,OPTIONAL_ARGUMENT,POSITIONAL} argument_type;


typedef struct custom_option {
  const char* long_name;
  /* Set to NULL for no short name. */
  const char* short_name;
  /* Same as in getopt struct option. */
  argument_type has_arg;
  /* Description of the argument. Set NULL for no description. */
  const char* help;
  bool optional;
} custom_option;


char* name_argument(custom_option* opt);

void get_args(int argc, char* const* argv, custom_option* options, bool* set, char** arguments, size_t nargs);

void print_help(const char* const argv0, const custom_option* const options, size_t nargs);

int check_required(bool* set, const custom_option* const options,size_t nargs);

void required_error(custom_option* option);

bool exclude(custom_option* options, const bool* set, const size_t** groups, const size_t* group_sizes, size_t ngroups, custom_option** conflict_a, custom_option** conflict_b);

void exclude_error(custom_option* conflict_a, custom_option* conflict_b);
#ifdef __cplusplus
}
#endif

#endif
