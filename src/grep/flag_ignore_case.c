#include <ctype.h>
#include <string.h>

#include "options.h"

// -i — ищем строку без учета регистра в указанном файле. Например, найдем
// строки с  UNIX, Unix, unix командой: grep -i "UNix" geekfile.txt.

char* my_strcasestr(const char* haystack, const char* needle) {
    if (!needle) return (char*)haystack;
    for (; haystack; haystack++) {
        if (tolower((unsigned char)*haystack) ==
            tolower((unsigned char)*needle)) {
            const char* h = haystack;
            const char* n = needle;
            while (tolower((unsigned char)*++h) ==
                       tolower((unsigned char)*++n) &&
                   *n);
            if (!*n) return (char*)haystack;
        }
    }
    return NULL;
}

void handle_i_flag(GrepOptions* options) { options->ignore_case = 1; }

int is_match(const char* line, GrepOptions* options) {
    int any_match = 0;
    for (int i = 0; i < options->pattern_count; i++) {
        const char* pattern = options->patterns[i];
        if (pattern[0] == '\0') continue;

        if (options->ignore_case) {
            if (my_strcasestr(line, pattern)) any_match = 1;
        } else {
            if (strstr(line, pattern)) any_match = 1;
        }
    }

    return options->invert_match ? !any_match : any_match;
}