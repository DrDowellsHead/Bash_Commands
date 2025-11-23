#include <stdio.h>

#include "options.h"

//-s Тихий режим
// Что делает : Подавляет сообщения об ошибках

//     bash
//         grep "hello" nonexistent.txt Обычно :
//      Ошибка: файл не существует
//     С -s : Просто ничего не выведет(но код ошибки будет)

int quiet_mode(const char filename, char pattern) {
    char r;
    char BUFFER[1024];

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror(NULL);
        return 1;
    }

    while (r = fgets(BUFFER, sizeof(BUFFER), file) != NULL) {
        printf("%s", BUFFER);
    }

    if (r = fgets(BUFFER, sizeof(BUFFER), file) == NULL) {
        perror(NULL);
    }

    fclose(file);

    return 0;
}