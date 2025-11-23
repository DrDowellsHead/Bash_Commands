#include <stdio.h>
#include <string.h>

#include "options.h"

// 5. - l Имена файлов
// Что делает : Показывает только имена файлов, где есть совпадения

//     bash
//        grep -l "hello" *.txt
// Выведет : text.txt(просто имя файла, а не строки)

int match_files_names(const char* filename, char pattern) {
    char r;
    char BUFFER[1024];

    if (fgets(BUFFER, sizeof(BUFFER), stdin) == NULL) {
        perror("Ошибка чтения ввода");
        return 1;
    }

    BUFFER[strcspn(BUFFER, "\n")] = '\0';

    if (strcmp(filename, BUFFER) == 0) {
        printf(filename);
    } else {
        printf("Совпадений не найдено");
    }

    return 0;
}