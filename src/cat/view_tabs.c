#include <stdio.h>
#include <string.h>

#include "options.h"

#define BUFFER_SIZE 32768

// Флаг -t
// Также отображает табы как ^I

int view_tabs(char* line, CatOption* options) {
  (void)options;

  int j = 0;
  char output[BUFFER_SIZE];

  for (int i = 0; line[i] != '\0' && j < BUFFER_SIZE; i++) {
    if (line[i] == '\t') {
      output[j++] = '^';
      output[j++] = 'I';
    } else {
      output[j++] = line[i];
    }
  }
  output[j] = '\0';

  strcpy(line, output);

  return 0;
}