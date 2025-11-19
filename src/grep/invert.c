#include <stdio.h>
#include <string.h>

#include "options.h"

//-v Инвертировать поиск Что делает : Выводит строки, которые НЕ содержат
// шаблон

//     bash grep -v "hello" file.txt Найдет : "Goodbye world", "test line"(все
//     КРОМЕ строк с "hello")

int invert(FILE* old_file, char pattern) {
    FILE *old_file_pointer, *new_file_pointer;
    char r;
    const char BUFFER[1024];

    old_file = fopen(old_file_pointer, "r");
    new_file = fopen(new_file_pointer, "w");

    if (old_file == NULL) {
        perror("Ошибка чтения файла");
        return 1;
    }

    while (r = fgets(BUFFER, sizeof(BUFFER), old_file) != EOF) {
        if (strstr(r, pattern) == NULL) {
            fputs(BUFFER, new_file);
        }

        fclose(old_file);
        fclose(new_file);

        remove(old_file);

        return 0;
    }