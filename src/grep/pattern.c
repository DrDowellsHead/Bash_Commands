#include <stdio.h>
#include <string.h>

#include "options.h"

//-e Шаблон
// Что делает: Позволяет указать несколько шаблонов для поиска

//                  bash:
//                  grep -e "hello" - e "world" file.txt
//     Найдёт строки, содержащие ИЛИ "hello" ИЛИ "world"

int pattern(const char* filename, char* patterns[]) {
    FILE* file_pointer;
    int r;
    char buffer[256];

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("Ошибка чтения файла");
        return 1;
    }

    while (r = fgets(buffer, sizeof(buffer), file) != EOF) {
        if (strstr(r, patterns) != NULL) {
            printf("Найдена строка: ", pattern);
        } else {
            printf("Строка не найдена");
        }
    }

    fclose(file);

    return 0;
}