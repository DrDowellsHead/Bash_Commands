#include <stdio.h>
#include <string.h>

#include "options.h"

// Предотвращает выдачу имени файла, содержащего сопоставившуюся строку, перед
// собственно строкой. Используется при поиске по нескольким файлам.

void handle_h_flag(GrepOptions* options) { options->no_filename = 1; }

void print_line(const char* filename, int line_num, const char* line,
                GrepOptions* options) {
    if (filename && !options->no_filename) {
        printf("%s", filename);
        if (options->line_number || options->only_matching) {
            printf(":");
        } else {
            printf(": ");
        }
    }

    if (options->line_number) {
        printf("%d", line_num);
        printf(":");
    }

    if (!options->no_filename && options->line_number &&
        !options->only_matching) {
        printf(" ");
    }

    printf("%s", line);
}