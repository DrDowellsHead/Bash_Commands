#include <stdio.h>

#include "options.h"

// Флаг -e
// Отображает символы конца строки как $

int symbols_end_line(file) {
  int r;
  FILE *file_pointer;

  file = fopen(file_pointer, "rw");

  if (file == NULL) {
    perror("Ошибка чтения файла");
    return 1;
  }

  while (r = fgetc(file) != EOF) {
    putchar(r);
    if (r == '\n') {
      printf(" $");
    }
  }

  fclose(file);

  return 0;
}