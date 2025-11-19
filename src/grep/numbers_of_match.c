#include <stdio.h>
#include <string.h>

#include "options.h"

//-c Количество совпадений Что делает: Показывает только цифру - сколько строк
// совпало

//   bash grep -
//       c "hello" file.txt Выведет : 2(нашлось 2 строки с "hello")

int numbers_of_match(FILE* file, char pattern) {
    FILE* file_pointer;
    char r;
    const BUFFER[1024];
    int count = 0;

    file = fopen(file_pointer, "r");

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