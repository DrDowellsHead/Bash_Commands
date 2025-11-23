#include <getopt.h>
#include <stdio.h>
#include <unistd.h>  // Для getopt

#include "options.h"
#define BUFFER \
    32768  // Фиксированный размер буффера для минимизации системных вызовов

int main(int argc,
         char *argv[]) {  // С помощью argc и argv читаю аргументы командной
                          // строки

    CatOption options = {0};
    int flag;

    // Обработка флагов. Если нет флагов, то getopt возвращает -1, а optind
    // указыввает на следующую строку после всех аргументов
    while (getopt(argc, argv, "benstET") != -1) {
        switch (flag) {
            case 'b':
                options.numbering_non_empty = 1;
                break;
            case 'e':
                options.symbols_end_line = 1;
                break;
            case 'E':
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
            case 'T':
                options.view_tabs = 1;
                break;
            default:
                printf("Введённый флаг не существует.");
                break;
        }
    }

    if (optind >= argc) {
        file_read(NULL, &options);  // Аргументов нет - вывод из stdin
    } else {
        for (int i = optind; i < argc; i++) {
            file_read(argv[i], &options);
        }
    }

    return 0;
}