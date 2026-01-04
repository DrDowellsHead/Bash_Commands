#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "options.h"

// Флаг -b
// Нумерует только непустые строки

int numbering_non_empty(char* line, CatOption* options, int* line_number) {
  (void)options;

  int is_empty = 1;

  for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
    if (!isspace((unsigned char)line[i])) {
      is_empty = 0;
      break;
    }
  }

  if (line[0] == '\n' || line[0] == '\0') {
    is_empty = 1;
  }

  if (!is_empty) {
    printf("%6d\t", (*line_number)++);
  }

  return 0;
}