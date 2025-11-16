#include <stdio.h>
#include "options.h"

//-e Шаблон
// Что делает: Позволяет указать несколько шаблонов для поиска

//                  bash:
//                  grep -e "hello" - e "world" file.txt
//     Найдёт строки, содержащие ИЛИ "hello" ИЛИ "world"

int pattern(file, char* a, char* b) {
    FILE* file_pointer;
    int r;

    file = fopen(file_pointer, "r");

    if (file == NULL) {
      perror("Ошибка чтения файла");
      return 1;
    }

    while (r = getc(file) != EOF)
    {
        if ()
    }
    
}