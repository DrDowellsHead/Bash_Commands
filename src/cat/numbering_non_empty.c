#include <stdio.h>
#include <string.h>

#include "options.h"

// Флаг -b
// Нумерует только непустые строки

int numbering_non_empty(file) {
  int number_str = 0;
  int r;
  FILE *file_pointer;

  file = fopen(file, "rw");

  if (file == NULL) {
    perror("Ошибка чтения файла");
    return 1;
  }

  while (r = fgetc(file) != EOF) {
    if (strlen(file) != 0) {
      printf("%d ", number_str);
      putchar(r);

      if (r == '\n') {
        number_str++;
        printf("%d ", number_str);
      } else {
        putchar(r);
      }
    }
  }

  fclose(file);

  return 0;
}