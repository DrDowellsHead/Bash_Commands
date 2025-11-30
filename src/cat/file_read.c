#include <stdio.h>

#include "options.h"

#define BUFFER_SIZE \
    32768  // Фиксированный размер буффера для минимизации системных вызовов

void file_read(const char* filename, CatOption* options) {
    FILE* file;
    char buffer[BUFFER_SIZE];
    int line_number = 1;
    int last_empty = 0;

    if (filename == NULL) {
        file = stdin;
    } else {
        file = fopen(filename, "r");
        if (file == NULL) {
            perror("Ошибка чтения файла");
            return;
        }
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char processed_line[BUFFER_SIZE];
        strcpy(processed_line, buffer);

        int should_print = 1;

        if (options->compession_str) {
            should_print = compession_str(processed_line, options, &last_empty);
        }

        if (!should_print) continue;

        if (options->numbering_non_empty) {
            numbering_non_empty(processed_line, options, &line_number);
        } else if (options->numbering_all_str) {
            numbering_all_str(processed_line, options, &line_number);
        }

        if (options->symbols_end_line) {
            symbols_end_line(processed_line, options);
        }

        if (options->view_tabs) {
            view_tabs(processed_line, options);
        }

        printf("%s", processed_line);
    }

    if (file != stdin) fclose(file);
}