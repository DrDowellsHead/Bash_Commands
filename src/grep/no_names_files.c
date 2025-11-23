#include <stdio.h>
#include <string.h>

#include "options.h"

// 7. -h Без имен файлов
//     Что делает:
//      Не показывает имена файлов(полезно при поиске в нескольких файлах)

//      bash
//          grep -h "hello" file1.txt file2.txt
//          Выведет только строки, без file1.txt : перед каждой

int no_nems_files(const char* filename, char* pattern[]) {
    char r;
    const BUFFER[1024];

    FILE* file = fopen(file, "r");

    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    if (fgets(BUFFER, sizeof(BUFFER), file) != NULL) {
        printf("%s", BUFFER);
    } else {
        perror("Ошибка чтения файла");
    }

    fclose(file);

    return 0;
}