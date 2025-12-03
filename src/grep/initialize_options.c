#include <stdlib.h>

#include "options.h"

void initialize_options(GrepOptions* options) {
    options->ignore_case = 0;
    options->invert_match = 0;
    options->count_only = 0;
    options->files_with_matches = 0;
    options->line_number = 0;
    options->no_filename = 0;
    options->silent_mode = 0;
    options->pattern_from_file = 0;
    options->only_matching = 0;
    options->pattern_flag = 0;
    options->patterns = NULL;
    options->pattern_count = 0;
}

void cleanup_options(GrepOptions* options) {
    for (int i = 0; i < options->pattern_count; i++) {
        free(options->patterns[i]);
    }
    free(options->patterns);
}