#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "options.h"

void process_arguments(GrepOptions* options, int argc, char** argv) {
    if (options->pattern_count == 0 && optind < argc) {
        add_pattern(options, argv[optind++]);
    }

    if (!validate_patterns(options)) {
        return;
    }

    if (optind >= argc) {
        file_read_grep(NULL, options);
    } else {
        for (int i = optind; i < argc; i++) {
            file_read_grep(argv[i], options);
        }
    }
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