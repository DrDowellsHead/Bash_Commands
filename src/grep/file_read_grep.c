#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

// Фиксированный размер буфера для оптимизации системных вызовов
#define BUFFER_SIZE 32768

void file_read_grep(const char* filename, GrepOptions* options, int* any_match,
                    int* any_error) {
    FILE* file;
    char buffer[BUFFER_SIZE];
    int line_number = 0;
    int match_count = 0;
    int file_opened = 0;
    *any_match = 0;
    *any_error = 0;

    if (filename == NULL) {
        file = stdin;
        file_opened = 1;
    } else {
        file = fopen(filename, "r");
        if (file == NULL) {
            if (!options->silent_mode) {
                perror(filename);
            }
            *any_error = 1;
            return;
        }
        file_opened = 1;
    }

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        line_number++;

        if (regex_match(buffer, options, NULL)) {
            match_count++;
            *any_match = 1;

            if (options->files_with_matches) {
                print_filename(filename, options);
                break;
            }

            if (options->count_only) {
                continue;
            }

            if (options->only_matching && !options->invert_match) {
                print_only_matches(filename, line_number, buffer, options);
            } else {
                print_line(filename, line_number, buffer, options);
            }
        }
    }

    if (options->count_only && !options->files_with_matches) {
        print_count(filename, match_count, options);
    }

    if (file_opened && file != stdin) {
        fclose(file);
    }

    if (match_count == 0) {
        *any_match = 0;
    }
}