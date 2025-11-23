#include <stdio.h>
#include <string.h>

#include "options.h"

// -f Шаблоны из файла
// Что делает:
// Берёт шаблоны для поиска из файла

//    bash
// #file patterns.txt содержит:
// #hello
// #world
//       grep -f patterns.txt file.txt
// Найдёт строки, содержащие "hello" ИЛИ "world"

int pattern_from_file(const char* filename, char* patterns[]) {
    char r;
    const BUFFER[1024];

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    while (r = fgets(BUFFER, sizeof(BUFFER), file) != NULL) {
        if (strstr(r, patterns) != NULL) {
            printf("%s", r);
        } else {
            perror("Ошибка чтения файла");
        }
    }

    fclose(file);

    return 0;
}