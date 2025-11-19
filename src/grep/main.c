#include <stdio.h>

#include "options.h"
#define BUFFER \
    32768  // Фиксированный размер буффера для минимизации системных вызовов

int main(int argc, char *argv[]) {
    GrepOption options = {0};
    int flag;

    if (argc == 0) {  // Нет аргементов - чтение из stdin
        if (fgets(BUFFER, sizeof(BUFFER), stdin) != NULL) {
            printf(BUFFER);
        } else {
            perror("Ошибка чтения файла");
        }
    }

    if (argc > 2) {
        while (getopt(argc, *argv, "eivclnhsfo")) {
            switch (flag) {
                case 'e':
                    options.pattern = 1;
                    break;
                case 'i':
                    options.ignore_regiser = 1;
                    break;
                case 'v':
                    options.invert = 1;
                    break;
                case 'c':
                    options.numbers_of_match = 1;
                    break;
                case 'l':
                    options.match_files_names = 1;
                    break;
                case 'n':
                    options.number_of_string = 1;
                    break;
                case 'h':
                    options.no_name_files = 1;
                    break;
                case 's':
                    options.quiet_mode = 1;
                    break;
                case 'f':
                    options.pattern_from_file = 1;
                    break;
                case 'o':
                    options.only_match = 1;
                    break;
                default:
                    printf("Введённый флаг не существует.");
                    break;
            }
        }
    }

    return 0;
}