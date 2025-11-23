#include <stdio.h>
#include <string.h>

#include "options.h"

//-c Количество совпадений Что делает: Показывает только цифру - сколько строк
// совпало

//   bash grep -
//       c "hello" file.txt Выведет : 2(нашлось 2 строки с "hello")

int numbers_of_match(const char* filename, char pattern) {
    char r;
    const BUFFER[1024];
    int count = 0;

    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        perror("Ошибка чтения файла");
        return 1;
    }

    while (r = fgets(BUFFER, sizeof(BUFFER), file) != NULL) {
        if (strstr(r, pattern) != NULL) {
            count++;
        }
    }

    printf("Количество совпадающих строк: ", count);

    fclose(file);

    return 0;
}