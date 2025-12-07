#include <getopt.h>
#include <stdio.h>
#include <unistd.h>  // Для getopt

#include "options.h"

// С помощью argc и argv читаю аргументы командной строки

int main(int argc, char* argv[]) {
    CatOption options = {0};
    int flag;
    int line_number = 1;  // Общий счетчик для всех файлов
    int last_empty = 0;   // Общее состояние для флага -s

    // Обработка флагов. Если нет флагов, то getopt возвращает -1, а optind
    // указыввает на следующую строку после всех аргументов
    // optind изначально равен 1. Если ./s21_cat -b -n file1.txt file2.txt :
    // argc = 
    // optind = 1
    // arg = argv[1] = "-b"
        // Начинается с '-', не "--" → флаг
        // Обрабатываем 'b', optind = 2

    // arg = argv[1] = "-n"
        // Начинается с '-', не "--" → флаг
        // Обрабатываем 'n', optind = 3

    // arg = argv[1] = "file1.txt"
        // НЕ начинается с '-' → НЕ флаг!
        // Прекращаем обработку, optind остается = 3

    while ((flag = getopt(argc, argv, "benstET")) != -1) {
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
        file_read(NULL, &options, &line_number,
                  &last_empty);  // Аргументов нет - вывод из stdin
    } else {
        for (int i = optind; i < argc; i++) {
            file_read(argv[i], &options, &line_number, &last_empty);
        }
    }

    return 0;
}