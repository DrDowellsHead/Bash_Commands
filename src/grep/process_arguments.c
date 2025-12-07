#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

int process_arguments(GrepOptions* options, int argc, char** argv) {
    if (options->pattern_count == 0 && optind < argc) {
        add_pattern(options, argv[optind++]);
    }

    // Проверка наличия шаблонов
    if (!validate_patterns(options)) {
        return 1;
    }

    if (!compile_regex(options)) {
        if (!options->silent_mode) {
            fprintf(stderr, "Недопустимый шаблон регулярного выражения\n");
        }
        return 1;
    }

    // Определяем, сколько файлов будет обрабатываться
    int file_count = argc - optind;
    options->file_count = file_count;

    // Если указан только один файл, по умолчанию не выводим имя файла
    if (file_count == 1 && !options->no_filename) {
        options->no_filename = 1;
    }

    if (optind >= argc) {
        file_read_grep(NULL, options);
    } else {
        for (int i = optind; i < argc; i++) {
            file_read_grep(argv[i], options);
        }
    }

    return 0;
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