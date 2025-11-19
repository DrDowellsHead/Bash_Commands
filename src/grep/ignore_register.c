#include <stdio.h>
#include <string.h>

#include "options.h"
// -i Игнорировать регистр
// Что делает : Ищет без учета больших / маленьких букв

//     bash
//         grep -i "hello" file.txt Найдет : "Hello world", "hello everyone"

int ignore_register(FILE* file, char pattern) {
    FILE* file_pointer;
    int r;
    char buffer[256];

    file = fopen(file_pointer, "r");

    if (file == NULL) {
        perror("Ошибка чтения файла");
        return 1;
    }

    while (r = fgets(buffer, sizeof(buffer), file) != EOF) {
        if (strstr(r, pattern) != NULL &
            strcasecmp(file, pattern) == 0) {  // Уверен, что не будет работать
            printf("Найдена строка: ", pattern);
        } else {
            printf("Строка не найдена");
        }
    }

    fclose(file);

    return 0;
}