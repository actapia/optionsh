#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "formatting.h"

/* This file is based on a file originally written for pa1. */

size_t max(size_t a, size_t b) {
  if (a <= b)
    return b;
  else
    return a;
}

void str_upper(char* upper_str, char* orig_str) {
  size_t orig_len = strlen(orig_str);
  for (size_t i=0; i<orig_len; i+=1) {
    upper_str[i] = toupper(orig_str[i]);
  }
  upper_str[orig_len] = 0;
}
