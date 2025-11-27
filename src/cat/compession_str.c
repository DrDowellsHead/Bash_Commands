#include <stdio.h>
#include <string.h>

#include "options.h"

// Флаг -s
// Сжимает несколько смежных пустых строк

int compession_str(char* line, CatOption* options, int* last_empty) {
    // Проверка на пустую строку
    int is_empty = (line[0] == '\n' || line == '\0');

    // Если шаблон пустой строки равен пустой строке, то выводим её
    if (is_empty && *last_empty) {
        return 0;
    }

    // Запоминаем состояние для следующей строки
    *last_empty = is_empty;

    return 1;
}