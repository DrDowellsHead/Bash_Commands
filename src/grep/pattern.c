#include <stdio.h>
#include <string.h>

#include "options.h"

//-e Шаблон
// Что делает: Позволяет указать несколько шаблонов для поиска

//                  bash:
//                  grep -e "hello" - e "world" file.txt
//     Найдёт строки, содержащие ИЛИ "hello" ИЛИ "world"

int pattern(const char* filename, char* patterns[]) {
    return strstr(filename, pattern) != NULL;
}