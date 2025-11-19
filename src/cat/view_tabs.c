#include <stdio.h>

#include "options.h"

// Флаг -t
// Также отображает табы как ^I

int view_tabs(file) {
    int r;
    FILE *file_pointer;

    file = fopen(file_pointer, "rw");

    if (file == NULL) {
        perror("Ошибка чтения файла");
        return 1;
    }

    while (r = getc(file) != EOF) {
        if (r == '\\t') {
            printf("^I");
        } else {
            putchar(r);
        }
    }

    fclose(file);

    return 0;
}