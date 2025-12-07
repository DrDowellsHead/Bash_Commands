#include <stdio.h>

#include "options.h"

// -c — находим количество строк, которые соответствуют заданному шаблону:
// grep -c "unix" geekfile.txt.

void handle_c_flag(GrepOptions* options) { options->count_only = 1; }

void print_count(const char* filename, int count, GrepOptions* options) {
    if (filename && options->file_count > 1 && !options->no_filename) {
        printf("%s:%d\n", filename, count);
    } else {
        printf("%d\n", count);
    }
}