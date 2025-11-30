#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

//-f — берем шаблоны из файла по одному на строку:
// cat pattern.txt
// Agarwal
// Aggarwal
// Agrawal
// grep –f pattern.txt geekfile.txt

void load_patterns_from_file(GrepOptions* options, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        if (!options->silent_mode) perror(filename);
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (buffer[0] != '\0') {
            add_pattern(options, buffer);
        }
    }
    fclose(file);
}

void handle_f_flag(GrepOptions* options, const char* optarg) {
    options->pattern_from_file = 1;
    load_patterns_from_file(options, optarg);
}