#include <stdio.h>
#include <string.h>

#include "options.h"

// -o — по умолчанию grep показывает всю строку, которая совпала по запросу. Но
// при помощи опции -o можно выбрать только определенное словосочетание:
//  grep -o "unix" geekfile.txt.

void print_only_matches(const char* filename, int line_num, const char* line,
                        GrepOptions* options) {
    const char* pos = line;
    int offset = 0;

    for (int i = 0; i < options->pattern_count; i++) {
        pos = line;
        offset = 0;
        regmatch_t match;

        while (1) {
            const char* search_start = pos;

            if (regexec(&options->regexes[i], search_start, 1, &match, 0) !=
                0) {
                break;
            }

            if (match.rm_so == -1) break;

            int print_filename = 0;
            if (filename) {
                if (!options->no_filename && options->file_count > 1) {
                    print_filename = 1;
                }
            }

            if (print_filename) {
                printf("%s", filename);
                if (options->line_number) printf(":");
            }

            if (options->line_number) {
                printf("%d:", line_num);
            }

            // Выводим совпавшую часть
            int start = match.rm_so + offset;
            int end = match.rm_eo + offset;

            for (int j = start; j < end; j++) {
                putchar(line[j]);
            }
            putchar('\n');

            // Сдвигаем позицию
            if (match.rm_eo > 0) {
                pos = search_start + match.rm_eo;
                offset += match.rm_eo;
            } else {
                pos++;
                offset++;
            }
        }
    }
}

void handle_o_flag(GrepOptions* options) { options->only_matching = 1; }