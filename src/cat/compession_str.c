#include <stdio.h>
#include <string.h>

#include "options.h"

// Флаг -s
// Сжимает несколько смежных пустых строк

int compession_str(file) {
    int r;
    FILE *old_file, *new_file;
    const char BUFFER[1024];

    old_file = fopen(file, "r");
    new_file = fopen(file, "w");

    if (old_file == NULL || new_file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    while (r = fgets(BUFFER, sizeof(BUFFER), old_file) != EOF) {
        if (strlen(old_file) != 0) {
            fputs(BUFFER, new_file);
        } else {
            fputc('\n', new_file);
        }
    }

    fclose(old_file);
    fclose(new_file);

    remove(old_file);

    return 0;
}