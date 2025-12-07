#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

int process_arguments(GrepOptions* options, int argc, char** argv) {
    int exit_code = 0;
    int any_match = 0;
    int any_error = 0;

    if (options->pattern_count == 0 && optind < argc) {
        add_pattern(options, argv[optind++]);
    }

    // Проверка наличия шаблонов
    if (!validate_patterns(options)) {
        return 2;
    }

    if (!compile_regex(options)) {
        if (!options->silent_mode) {
            fprintf(stderr, "Недопустимый шаблон регулярного выражения\n");
        }
        return 2;
    }

    // Определяем, сколько файлов будет обрабатываться
    int file_count = argc - optind;
    options->file_count = file_count;

    // Если указан только один файл, по умолчанию не выводим имя файла
    if (file_count == 1 && !options->no_filename) {
        options->no_filename = 1;
    }

    if (optind >= argc) {
        file_read_grep(NULL, options, &any_match, &any_error);
    } else {
        for (int i = optind; i < argc; i++) {
            int file_has_match = 0;
            int file_error = 0;
            file_read_grep(argv[i], options, &file_has_match, &file_error);

            if (file_error) {
                any_error = 1;
            }
            if (file_has_match) {
                any_match = 1;
            }
        }
    }

    if (any_error) {
        exit_code = 2;
    } else if (!any_match) {
        exit_code = 1;
    } else {
        exit_code = 0;
    }

    return exit_code;
}

int validate_patterns(GrepOptions* options) {
    if (options->pattern_count == 0) {
        if (!options->silent_mode) {
            fprintf(stderr, "Шаблон не указан\n");
        }
        return 0;
    }
    return 1;
}