#include <stdio.h>

#include "options.h"

// 6. -n Номера строк

// Что делает : Показывает номер строки в файле

//   bash grep -n
//      "hello" file.txt
//      Выведет :

//      1: Hello world
//      2: hello everyone

int number_of_strings(const char* filename, char pattern) {
    const char BUFFER[1024];
    int string_count = 0;
    char r;

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("Ошибка чтения файла");
        return 1;
    }

    while (r = fgets(BUFFER, sizeof(BUFFER), file)) {
        if (r == '\n') {
            string_count++;
        }
    }

    printf("%d: %s", string_count, r);

    fclose(file);

    return 0;
}
