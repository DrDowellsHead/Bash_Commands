#include <stdio.h>
#include <string.h>

#include "options.h"

// Флаг -b
// Нумерует только непустые строки

int numbering_non_empty(char* line, CatOption* options, int* line_number) {
    (void)options;

    if (line[0] != '\n' && line[0] != '\0') {
        // %6d - спецификатор формата для целого числа со знаком в десятичной
        // системе и выравниваем по правому краю
        printf("%6d ", (*line_number)++);
    } else {
        printf(" ");
    }

    return 0;
}