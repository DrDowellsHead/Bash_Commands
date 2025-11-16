#include <stdio.h>
#include <unistd.h>

#include "options.h"
#define BUFFER \
  32768  // Фиксированный размер буффера для минимизации системных вызовов

int main(
    int argc,
    int *argv[]) {  // С помощью argc и argv читаю аргументы командной строки

  CatOption options = {0};
  int flag;

  if (argc == 1) {  // Нет аргементов - чтение из stdin
    if (fgets(BUFFER, sizeof(BUFFER), stdin) != NULL) {
      printf(BUFFER);
    } else {
      perror("Ошибка чтения файла");
    }
  }

  if (argc > 1) {
    while (getopt(argc, *argv, "benst") == -1) {
      switch (flag) {
        case 'b':
          options.numbering_non_empty = 1;
          break;
        case 'e':
          options.symbols_end_line = 1;
          break;
        case 'n':
          options.numbering_all_str = 1;
          break;
        case 's':
          options.compession_str = 1;
          break;
        case 't':
          options.view_tabs = 1;
          break;
        default:
          printf("Введённый флаг не существует.");
          break;
      }
    }
  }
}