#include <stdio.h>
#include <string.h>

#include "options.h"

//-v Инвертировать поиск Что делает : Выводит строки, которые НЕ содержат
// шаблон

//     bash grep -v "hello" file.txt Найдет : "Goodbye world", "test line"(все
//     КРОМЕ строк с "hello")

int invert(const char* filename, char pattern) {
    FILE* new_file_pointer;
    char r;
    const char BUFFER[1024];

    FILE* old_file = fopen(filename, "r");
    FILE* new_file = fopen(new_file_pointer, "w");

    if (old_file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    while (r = fgets(BUFFER, sizeof(BUFFER), old_file) != NULL) {
        if (strstr(r, pattern) == NULL) {
            fputs(BUFFER, new_file);
        } else {
            perror("Ошибка чтения файла");
        }

        fclose(old_file);
        fclose(new_file);

        remove(old_file);

        return 0;
    }
}