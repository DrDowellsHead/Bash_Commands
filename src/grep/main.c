#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "options.h"

int main(int argc, char* argv[]) {
    GrepOption options = {0};
    char* pattern = NULL;
    int flag;

    while ((flag = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
        switch (flag) {
            case 'e':
                options.pattern = 1;
                pattern = optarg;
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
                pattern = optarg;
                break;
            case 'o':
                options.only_match = 1;
                break;
            default:
                if (!options.quiet_mode) {
                    fprintf(stderr, "Недопостуимый флаг\n");
                }
                return 1;
        }
    }

    if (pattern == NULL && optind < argc) {
        pattern = argv[optind];
        optind++;
    }

    if (pattern == NULL) {
        if (!options.quiet_mode) {
            fprintf(stderr, "Не указан шаблон для поиска\n");
        }
        return 1;
    }

    if (optind >= argc) {
        file_read_grep(NULL, &options, pattern);
    } else {
        for (int i = optind; i < argc; i++) {
            file_read_grep(argv[i], &options, pattern);
        }
    }

    return 0;
}