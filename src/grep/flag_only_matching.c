#include <stdio.h>
#include <string.h>

#include "options.h"

// -o — по умолчанию grep показывает всю строку, которая совпала по запросу. Но
// при помощи опции -o можно выбрать только определенное словосочетание:
//  grep -o "unix" geekfile.txt.

void print_only_matches(const char* filename, int line_num, const char* line,
                        GrepOptions* options) {
    for (int i = 0; i < options->pattern_count; i++) {
        const char* pattern = options->patterns[i];
        if (pattern[0] == '\0') continue;

        const char* pos = line;
        size_t len = strlen(pattern);

        while (1) {
            const char* match;
            if (options->ignore_case) {
                match = my_strcasestr(pos, pattern);
            } else {
                match = strstr(pos, pattern);
            }

            if (!match) break;

            if (filename && !options->no_filename) {
                printf("%s", filename);
                if (options->line_number) {
                    printf(":");
                } else {
                    printf(": ");
                }
            }

            if (options->line_number) {
                printf("%d", line_num);
                printf(":");
            }

            if (!options->no_filename && options->line_number) {
                printf(" ");
            }

            fwrite(match, 1, len, stdout);
            putchar('\n');

            pos = match + len;
        }
    }
}

void handle_o_flag(GrepOptions* options) { options->only_matching = 1; }