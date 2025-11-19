#include <stdio.h>

#include "options.h"

void file_read(file) {
    int r;
    FILE* file_pointer;

    file = fopen(file_pointer, "r");

    if (file == NULL) {
        perror("Ошибка чтения файла");
        return 1;
    }

    while (r = fgetc(file) != EOF) {
        putchar(r);
    }

    fclose(file);
}