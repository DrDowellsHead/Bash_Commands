#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

#define BUFFER_SIZE 32768

void file_read_grep(const char* filename, GrepOption* options, const char* pattern) {
    FILE* file;
    char buffer[BUFFER_SIZE];
    int line_number = 0;

    if (filename == NULL) {
        file = stdin;
    } else {
        file = fopen(filename, "r");
        if (file == NULL) {
            quiet_mode(filename, pattern, options);
            return;
        }
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        line_number++;
        
        if (options->ignore_regiser) {
            ignore_register(filename, pattern, options);
        } else if (options->invert) {
            invert(filename, pattern, options);
        } else if (options->numbers_of_match) {
            numbers_of_match(filename, pattern, options);
        } else if (options->match_files_names) {
            match_files_names(filename, pattern, options);
        } else if (options->number_of_string) {
            number_of_string(filename, pattern, options);
        } else if (options->no_name_files) {
            no_name_files(filename, pattern, options);
        } else if (options->pattern_from_file) {
            pattern_from_file(filename, pattern, options);
        } else if (options->only_match) {
            only_match(filename, pattern, options);
        } else if (options->pattern) {
            pattern(filename, pattern, options);
        }
    }

    if (file != stdin) {
        fclose(file);
    }
}