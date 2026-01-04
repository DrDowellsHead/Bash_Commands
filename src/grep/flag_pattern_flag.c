#include <stdlib.h>
#include <string.h>

#include "options.h"

// -e — задаем выражение с этой опцией, которое можно использовать несколько
// раз:
// grep -e "Agarwal"-e "Aggarwal" -e "Agrawal" geekfile.txt.

void add_pattern(GrepOptions* options, const char* pattern) {
  options->patterns =
      realloc(options->patterns, (options->pattern_count + 1) * sizeof(char*));
  options->patterns[options->pattern_count] = strdup(pattern);
  options->pattern_count++;
}

void handle_e_flag(GrepOptions* options, const char* optarg) {
  options->pattern_flag = 1;
  add_pattern(options, optarg);
}