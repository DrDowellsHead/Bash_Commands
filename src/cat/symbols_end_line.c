#include <stdio.h>
#include <string.h>

#include "options.h"

// Флаг -e
// Отображает символы конца строки как $

int symbols_end_line(char* line, CatOption* options) {
    size_t len = strlen(line);

    if (len > 0 && line[len - 1] == '\n') {
        line[len - 1] = '\0';
        strcat(line, "&\n");
    }

    return 0;
}