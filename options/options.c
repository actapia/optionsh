#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "formatting.h"
#include "options.h"

#define NOT_LONG -1

/* This file is based on a file originally written for pa1. */

char* name_argument(custom_option* opt) {
  if (opt->long_name != NULL) {
    return opt->long_name;
  }
  else {
    return opt->short_name;
  }
}

void get_args(int argc, char* const* argv, custom_option* options, bool* set, char** arguments, size_t nargs) {
  /* Initialize set and arguments. */
  for (size_t i = 0; i<nargs; i+=1) {
    set[i] = false;
    arguments[i] = NULL;
  }
  /* Get size of buffers used for getopt. */
  size_t long_options_size = 0;
  size_t short_options_length = 0;
  size_t positionals_size = 0;
  for (size_t i = 0; i<nargs; i+=1) {
    if (options[i].has_arg != POSITIONAL) {
      if (options[i].long_name != NULL) {
	long_options_size+=1;
      }
      if (options[i].short_name != NULL) {
	short_options_length += 1;
	if (options[i].has_arg == REQUIRED_ARGUMENT) {
	  short_options_length += 1;
	}
	else if (options[i].has_arg == OPTIONAL_ARGUMENT) {
	  short_options_length += 2;
	}
      }
    }  
    else {
      positionals_size+=1;
    }
  }
  /* Generate buffers used with getopt. */
  struct option* long_options = malloc(sizeof(struct option)*(long_options_size+1));
  char* short_options = malloc(sizeof(char)*(short_options_length+1));
  /* positional_indices stores the indies of the positional arguments. */
  size_t* positional_indices = malloc(sizeof(size_t)*positionals_size);
  size_t long_options_index = 0;
  size_t short_options_index = 0;
  size_t positional_indices_index = 0;
  /* short_position maps characters to their positions in the set and arugments arrays.
     This is feasible because a char occupies only a single byte, and, hence, there are only 256
     possibilities for a char's value. Nevertheless, this is typically somewhat wasteful; a hash
     table that can expand dynamically would probably be a more space-efficient solution. However,
     I did not have time to implement such a solution, and I expect this will also have the advantage
     of being faster than a hash table.
  */
  size_t short_position[256];
  int long_pos = NOT_LONG;
  for (size_t i = 0; i<nargs; i+=1) {
    if (options[i].has_arg != POSITIONAL) {
      if (options[i].long_name != NULL) {
	long_options[long_options_index].name = options[i].long_name;
	long_options[long_options_index].has_arg = options[i].has_arg;
	long_options[long_options_index].flag = &long_pos;
	long_options[long_options_index].val = i;
	long_options_index+=1;
      }
      if (options[i].short_name != NULL) {
	short_options[short_options_index++] = *options[i].short_name;
	if (options[i].has_arg == REQUIRED_ARGUMENT) {
	  short_options[short_options_index++] = ':';	  
	}
	else if (options[i].has_arg == OPTIONAL_ARGUMENT) {
	  short_options[short_options_index++] = ':';
	  short_options[short_options_index++] = ':';
	}
	short_position[(unsigned char)*options[i].short_name] = i;	
      }
    }
    else {
      positional_indices[positional_indices_index++] = i;
    }
  }  
  long_options[long_options_index].name = NULL;
  long_options[long_options_index].has_arg = 0;
  long_options[long_options_index].flag = NULL;
  long_options[long_options_index].val = 0;
  short_options[short_options_index] = 0;
  int result;
  int index = 0;
  while ((result = getopt_long(argc,argv,short_options,long_options,&index)) >= 0) {
    if (result != '?') {
      size_t arg_index;
      if (long_pos != NOT_LONG) {
	arg_index = long_pos;
      }
      else {
	arg_index = short_position[result];

      }
      if (!set[arg_index]) {
	set[arg_index] = true;
	arguments[arg_index] = optarg;
      }
      else {
	/* Argument was set multiple times. Provide error message. */
      }   
      long_pos = NOT_LONG;
    }
  }
  /* Handle positional arguments. */
  /* It is assumed that positional arguments given in options are provided in the order in which they 
     are intended to appear on the command line.
  */
  int argv_index = optind;
  positional_indices_index = 0;
  /*printf("%d < %d, %d < %d\n",argv_index,argc,set_index,nargs);*/
  while ((argv_index < argc) && (positional_indices_index < positionals_size)) {
    set[positional_indices[positional_indices_index]] = true;
    arguments[positional_indices[positional_indices_index]] = argv[argv_index];
    argv_index+=1;
    positional_indices_index+=1;
  }
  if ((argv_index < argc) || (positional_indices_index < positionals_size)) {
    /* Too few or too many arguments. Fail. */
  }
  free(long_options);
  free(short_options);
  free(positional_indices);
}

void print_help(const char* const argv0, const custom_option* const options, size_t nargs) {
  /* Create parts of usage string. */
  char** argument_strings = malloc(sizeof(char*)*nargs);
  for (size_t i = 0; i<nargs; i+=1) {
    if (options[i].has_arg == POSITIONAL) {
      argument_strings[i] = name_argument(&options[i]);
    }
    else {
      /* This accounts for the dash. */
      size_t string_size = 1;
      if (options[i].optional) {
	/* This accounts for the two brackets. */
	string_size+=2;
      }
      char* name;
      if (options[i].long_name != NULL) {
	name = options[i].long_name;
	/* This accounts for the extra dash. */
	string_size+=1;
      }
      else {
	name = options[i].short_name;
      }
      /* The name of the argument must appear at least once. */
      size_t name_len = strlen(name);
      string_size+=name_len;
      if (options[i].has_arg != NO_ARGUMENT) {
	/* This accounts for the space/equals sign and the "metavar." */
	string_size+=1+name_len;
      }
      if (options[i].has_arg == OPTIONAL_ARGUMENT) {
	/* This accounts for extra brackets around the metavar. */
	string_size+=2;
      }
      argument_strings[i] = malloc(sizeof(char*)*(string_size+1));
      size_t argument_string_index = 0;
      if (options[i].optional) {
	argument_strings[i][argument_string_index++] = '[';
      }
      argument_strings[i][argument_string_index++] = '-';
      if (options[i].long_name != NULL) {
	argument_strings[i][argument_string_index++] = '-';
      }
      strcpy(&argument_strings[i][argument_string_index],name);
      argument_string_index+=name_len;
      if (options[i].has_arg != NO_ARGUMENT) {
	if (options[i].has_arg == REQUIRED_ARGUMENT) {
	  argument_strings[i][argument_string_index++] = ' ';
	}
	else {
	  argument_strings[i][argument_string_index++] = '[';
	  argument_strings[i][argument_string_index++] = '=';
	}
	char* metavar = malloc(sizeof(char*)*(name_len+1));
	str_upper(metavar,name);
	strcpy(&argument_strings[i][argument_string_index],metavar);
	free(metavar);
	argument_string_index+=name_len;
	if (options[i].has_arg == OPTIONAL_ARGUMENT) {
	  argument_strings[i][argument_string_index++] = ']';
	}
      }
      if (options[i].optional) {
	argument_strings[i][argument_string_index++] = ']';
      }
      argument_strings[i][argument_string_index++] = 0;
    }
  }
  printf("Usage: %s",argv0);
  for (size_t i=0; i < nargs; i+=1) {
    printf(" %s",argument_strings[i]);
    if (options[i].has_arg != POSITIONAL) {
      free(argument_strings[i]);
    }
  }
  printf("\n\n");
  free(argument_strings);
  if (nargs > 0) {
    char** table_strings = malloc(sizeof(char*)*nargs);
    size_t positional_arguments = 0;
    size_t optional_arguments = 0;
    size_t required_arguments = 0;
    size_t max_length = 0;
    for (size_t i = 0; i<nargs; i+=1) {
      char* name = name_argument(&options[i]);
      size_t name_len = strlen(name);
      if (options[i].has_arg == POSITIONAL) {
	table_strings[i] = name;
	positional_arguments += 1;
	max_length = max(max_length,name_len);
      }
      else {
	size_t table_string_len = 0;
	if (options[i].long_name != NULL) {
	  /* Accounts for two dashes and long name. */
	  table_string_len+=2+strlen(options[i].long_name);
	}
	if (options[i].short_name != NULL) {
	  /* Accounts for one dash and short name. */
	  table_string_len+=1+strlen(options[i].short_name);       
	}
	if ((options[i].short_name != NULL) && (options[i].long_name != NULL)) {
	  /* Accounts for comma and space between long and short names. */
	  table_string_len+=2;
	}
	if (options[i].has_arg != NO_ARGUMENT) {
	  /* Accounts for space/equals sign and metavar. */
	  table_string_len+=1+name_len;
	}
	table_strings[i] = malloc(sizeof(char)*(table_string_len+1));
	size_t table_string_index = 0;
	if (options[i].short_name != NULL) {
	  /* Add short name to table_string. */
	  table_strings[i][table_string_index++] = '-';
	  table_strings[i][table_string_index++] = *options[i].short_name;
	}
	if (options[i].long_name != NULL) {
	  if (options[i].short_name != NULL) {
	    /* Add comma and space. */
	    table_strings[i][table_string_index++] = ',';
	    table_strings[i][table_string_index++] = ' ';
	  }
	  /* Add long name to table_string. */
	  table_strings[i][table_string_index++] = '-';
	  table_strings[i][table_string_index++] = '-';
	  strcpy(&table_strings[i][table_string_index],options[i].long_name);
	  table_string_index+=strlen(options[i].long_name);
	}
	if (options[i].has_arg != NO_ARGUMENT) {
	  if (options[i].has_arg == REQUIRED_ARGUMENT) {
	    table_strings[i][table_string_index++] = ' ';
	  }
	  else {
	    table_strings[i][table_string_index++] = '=';
	  }
	  /* Add metavar. */
	  char* metavar = malloc(sizeof(char*)*(name_len+1));
	  str_upper(metavar,name);
	  strcpy(&table_strings[i][table_string_index],metavar);
	  free(metavar);
	  table_string_index+=name_len;
	}
	table_strings[i][table_string_index] = 0;
	max_length = max(max_length,table_string_index);
	if (options[i].optional) {
	  optional_arguments+=1;
	}
	else {
	  required_arguments+=1;
	}
      }
    }
    char** positional_strings = malloc(sizeof(char*)*positional_arguments);
    char** positional_help = malloc(sizeof(char*)*positional_arguments);
    char** optional_strings = malloc(sizeof(char*)*optional_arguments);
    char** optional_help = malloc(sizeof(char*)*optional_arguments);
    char** required_strings = malloc(sizeof(char*)*required_arguments);
    char** required_help = malloc(sizeof(char*)*required_arguments);
    size_t positional_index = 0;
    size_t optional_index = 0;
    size_t required_index = 0;
    for (size_t i=0; i<nargs; i+=1) {
      if (options[i].has_arg == POSITIONAL) {
	positional_strings[positional_index] = table_strings[i];
	positional_help[positional_index] = options[i].help;
	positional_index+=1;
      }
      else {
	if (options[i].optional) {
	  optional_strings[optional_index] = table_strings[i];
	  optional_help[optional_index] = options[i].help;
	  optional_index+=1;
	}
	else {
	  required_strings[required_index] = table_strings[i];
	  required_help[required_index] = options[i].help;
	  required_index+=1;
	}
      }
    }
    /* Print table. */
    if (positional_arguments>0) {
      printf("positional arguments:\n");
      for (size_t i=0; i<positional_arguments; i+=1) {
	printf("  %*s",-(int)max_length,positional_strings[i]);
	if (positional_help[i] != NULL) {
	  printf("   %s",positional_help[i]);
	}
	printf("\n");
      }
      printf("\n");
    }
    if (required_arguments>0) {
      printf("required arguments:\n");
      for (size_t i=0; i<required_arguments; i+=1) {
	printf("  %*s",-(int)max_length,required_strings[i]);
	if (required_help[i] != NULL) {
	  printf("   %s",required_help[i]);
	}
	printf("\n");
      }
      printf("\n");
    }
    if (optional_arguments>0) {
      printf("optional arguments:\n");
      for (size_t i=0; i<optional_arguments; i+=1) {
	printf("  %*s",-(int)max_length,optional_strings[i]);
	if (optional_help[i] != NULL) {
	  printf("   %s",optional_help[i]);
	}
	printf("\n");
      }
      printf("\n");
    }
    for (size_t i=0; i<nargs; i+=1) {
      if (options[i].has_arg != POSITIONAL) {
	free(table_strings[i]);
      }
    }
    free(positional_strings);
    free(positional_help);
    free(optional_strings);
    free(optional_help);
    free(required_strings);
    free(required_help);
    free(table_strings);
  }
  else {
    printf("This program accepts no arguments.\n");
  }
}

int check_required(bool* set, const custom_option* const options,size_t nargs) {
  /* Returns the index of the first required argument not satisfied, or -1 otherwise. */
  for (size_t i=0; i<nargs; i+=1) {
    if ((!options[i].optional) && (!set[i])) {
      return i;
    }
  }
  return ALL_REQUIRED_SET;
}

const char* get_option_dash(const custom_option* option) {
  static const char* POSITIONAL_DASH = "";
  static const char* LONG_DASH = "--";
  static const char* SHORT_DASH = "-";
  if (option->long_name != NULL) {
    if (option->has_arg != POSITIONAL) {
      return LONG_DASH;
    }
    return POSITIONAL_DASH;
  }
  else {
    return SHORT_DASH;
  }
}

void required_error(custom_option* option) {
  printf("Missing required argument ");
  const char* option_dash = get_option_dash(option);
  char* name = name_argument(option);
  printf("%s%s.\n",option_dash,name);
}

bool exclude(custom_option* options, const bool* set, const size_t** groups, const size_t* group_sizes, size_t ngroups, custom_option** conflict_a, custom_option** conflict_b) {
  /* Checks if any options from differing mututally exclusive groups have been set.
     If any conflicting options are found, conflict_a and conflict_b are set to two such options from
     different groups.
     groups should be an array of arrays representing the mutually exclusive groups. Each element of
     an inner array should be an index of an option in the options array that should be in the group
     the inner array represents.
  */
  const int NONE_SEEN = -1;
  /* last_group is the index of the last group for which an option was set, or -1 if no set options have
     been seen yet. */
  long long last_group = NONE_SEEN;
  custom_option* last_option = NULL;
  for (size_t group_index=0; group_index<ngroups; group_index+=1) {
    for (size_t group_option_index=0; group_option_index<group_sizes[group_index]; group_option_index+=1) {
      if (set[groups[group_index][group_option_index]]) {
	if ((last_group != NONE_SEEN) && (last_group != group_index)) {
	  *conflict_a = last_option;
	  *conflict_b = &options[groups[group_index][group_option_index]];
	  return true;
	}
	else {
	  last_group = group_index;
	  last_option = &options[groups[group_index][group_option_index]];
	}
      }
    }
  }
  *conflict_a = NULL;
  *conflict_b = NULL;
  return false;
}

void exclude_error(custom_option* conflict_a, custom_option* conflict_b) {
  printf("Error: Argument %s%s cannot be used with argument %s%s.\n",
	 get_option_dash(conflict_a),
	 name_argument(conflict_a),
	 get_option_dash(conflict_b),
	 name_argument(conflict_b));
}


