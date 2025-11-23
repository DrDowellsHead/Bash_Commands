#include <stdio.h>
#include <string.h>

#include "options.h"

// -o Только совпавшая часть
//     Что делает:
//     Показывает только ту часть строки, которая совпала с шаблоном

//     bash
//         grep -o "hello" file.txt
//     Выведет:

//         text hello
//         hello(только слово "hello", а не всю строку)

int only_match(const char filename, char pattern) {
    char r;
    const BUFFER[1024];

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    while (r = fgets(BUFFER, sizeof(BUFFER), file) != NULL) {
        if (strstr(r, pattern) != NULL) {
            printf("%s", r);
        } else {
            perror("Ошибка чтения файла");
        }
    }

    fclose(file);

    return 0;
}