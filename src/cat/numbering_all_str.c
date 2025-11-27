#include <stdio.h>
#include <string.h>

#include "options.h"

// Флаг -n
// Нумерует все выходные строки

int numbering_all_str(char* line, CatOption* options, int* line_number) {
    printf("%6d\t", (*line_number)++);

    return 1;
}