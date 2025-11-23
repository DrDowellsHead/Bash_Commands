#include <stdio.h>
#include <unistd.h>

#include "options.h"
#define BUFFER_SIZE \
    32768  // Фиксированный размер буффера для минимизации системных вызовов

int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];
    GrepOption options = {0};
    int flag;

    if (argc == 0) {  // Нет аргументов - чтение из stdin
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf(buffer);
        } else {
            perror("Ошибка чтения файла");
        }
    }

    if (argc > 1) {
        while (getopt(argc, *argv, "e:ivclnh:sf:o") != -1) {
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