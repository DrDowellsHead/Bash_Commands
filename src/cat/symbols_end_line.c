#include <stdio.h>
#include "options.h"

// Флаг -e
// Отображает символы конца строки как $

int symbols_end_line(file) {
    int r;
    FILE *file_pointer;

    file_pointer = fopen(file_pointer, "rw");

    if (file_pointer == NULL) {
        perror("Ошибка чтения файла");
        return 1;
    }

    while (r = fgetc(file_pointer) != EOF) {
        putchar(r);
        if (r == '\n') {
            printf(" $");
    }

    return 0;
}