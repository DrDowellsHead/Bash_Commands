#include <stdio.h>
#include <string.h>

#include "options.h"

// Предотвращает выдачу имени файла, содержащего сопоставившуюся строку, перед
// собственно строкой. Используется при поиске по нескольким файлам.

void handle_h_flag(GrepOptions* options) { options->no_filename = 1; }

void print_line(const char* filename, int line_num, const char* line,
                GrepOptions* options) {
  int print_filename = 0;

  if (filename && !options->no_filename) {
    // Выводим имя файла только для нескольких файлов
    if (options->file_count > 1) {
      print_filename = 1;
    }
  }

  if (print_filename) {
    printf("%s:", filename);
  }

  if (options->line_number) {
    printf("%d:", line_num);
  }

  printf("%s", line);

  size_t len = strlen(line);
  if (len > 0 && line[len - 1] != '\n') {
    putchar('\n');
  }
}