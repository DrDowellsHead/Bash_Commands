#include <stdio.h>
#include <string.h>
#include "options.h"

// Флаг -n
// Нумерует все выходные строки

int numbering_all_str(file) {
    int number_str = 0;
    int r;
    FILE *file_pointer;

    file_pointer = fopen(file, "rw");

    if (file_pointer == NULL) {
        perror("Ошибка чтения файла");
        return 1;
    }

    while (r = getc(file_pointer) != EOF) {
        printf("%d ", number_str);

        if (r == '\n') {
            number_str++;
            printf("%d ", number_str);
        } else {
            putchar(r);
        }
    }
    
    return 0;
}