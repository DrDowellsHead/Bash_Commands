#include <stdio.h>

#include "options.h"

// -l — отображаем файлы, которые содержат заданную строку или шаблон:
// grep -l "unix" * или grep -l "unix" f1.txt f2.txt f3.xt f4.txt.

void handle_l_flag(GrepOptions* options) {
  options->files_with_matches = 1;
  // При флаге -l всегда выводим имена файлов, даже для одного файла
}

void print_filename(const char* filename, GrepOptions* options) {
  (void)options;
  if (filename) {
    printf("%s\n", filename);
  }
}