#include <regex.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

int compile_regex(GrepOptions* options) {
  if (options->regex_compiled) return 1;

  if (options->pattern_count == 0) return 0;

  options->regexes = malloc(options->pattern_count * sizeof(regex_t));
  if (!options->regexes) return 0;

  int cflags = REG_EXTENDED | REG_NEWLINE;
  if (options->ignore_case) cflags |= REG_ICASE;

  for (int i = 0; i < options->pattern_count; i++) {
    if (regcomp(&options->regexes[i], options->patterns[i], cflags) != 0) {
      for (int j = 0; j < i; j++) {
        regfree(&options->regexes[j]);
      }
      free(options->regexes);
      options->regexes = NULL;
      return 0;
    }
  }

  options->regex_compiled = 1;
  return 1;
}

int regex_match(const char* line, GrepOptions* options, regmatch_t* match) {
  int any_match = 0;

  for (int i = 0; i < options->pattern_count; i++) {
    int result;
    if (match) {
      result = regexec(&options->regexes[i], line, 1, match, 0);
    } else {
      result = regexec(&options->regexes[i], line, 0, NULL, 0);
    }

    if (result == 0) {
      any_match = 1;
      break;
    }
  }

  return options->invert_match ? !any_match : any_match;
}

void free_regex(GrepOptions* options) {
  if (options->regexes) {
    for (int i = 0; i < options->pattern_count; i++) {
      regfree(&options->regexes[i]);
    }
    free(options->regexes);
    options->regexes = NULL;
  }
  options->regex_compiled = 0;
}