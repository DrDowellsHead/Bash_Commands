#include <stdio.h>
#include <string.h>

#include "options.h"

// Предотвращает выдачу имени файла, содержащего сопоставившуюся строку, перед
// собственно строкой. Используется при поиске по нескольким файлам.

void handle_h_flag(GrepOptions* options) { options->no_filename = 1; }

void print_line(const char* filename, int line_num, const char* line,
                GrepOptions* options) {

    int print_filename = 0;

    if (filename) {
        // По умолчанию имя файла выводится только для нескольких файлов
        // или если явно не указан флаг -h
        if (!options->no_filename) {
            print_filename = 1;
        }
    }

    if (print_filename) {
        printf("%s", filename);
        if (options->line_number || options->only_matching) {
            printf(":");
        }
    }

    if (options->line_number) {
        printf("%d", line_num);
        printf(":");
    }

    printf("%s", line);
}