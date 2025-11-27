#ifndef OPTIONS_H
#define OPTIONS_H

// Опции Описание

//     1 -
//     e Шаблон.

//     2 -
//     i Игнорирует различия регистра.

//     3 -
//     v Инвертирует смысл поиска соответствий.

//     4 -
//     c Выводит только количество совпадающих строк.

//     5 -
//     l Выводит только совпадающие файлы.

//     6 -
//     n Предваряет каждую строку вывода номером строки из файла ввода.

//     7 -
//     h Выводит совпадающие строки,
//     не предваряя их именами файлов.

//         8 -
//         s Подавляет сообщения об ошибках о несуществующих или нечитаемых
//         файлах.

//         9 -
//         f file Получает регулярные выражения из файла.

//         10 -
//         o Печатает только совпадающие(непустые)
// части совпавшей строки.

// Структура для работы с флагами команды grep
typedef struct {
    int pattern;            // Флан -e
    int ignore_regiser;     // Флаг -i
    int invert;             // Флаг -v
    int numbers_of_match;   // Флаг -c
    int match_files_names;  // Флаг -l
    int number_of_string;   // Флаг -n
    int no_name_files;      // Флаг -h
    int quiet_mode;         // Флаг -s
    int pattern_from_file;  // Флаг -f
    int only_match;         // Флаг -o
} GrepOption;

void file_read_grep(const char* filename, GrepOption* options,
                    const char* pattern);
int ignore_register(const char* filename, const char* pattern,
                    GrepOption* options);
int invert(const char* filename, const char* pattern,
                    GrepOption* options);
int numbers_of_match(const char* filename, const char* pattern,
                    GrepOption* options);
int match_files_names(const char* filename, const char* pattern,
                    GrepOption* options);
int number_of_string(const char* filename, const char* pattern,
                    GrepOption* options);
int no_names_files(const char* filename, const char* pattern,
                    GrepOption* options);
int quiet_mode(const char* filename, const char* pattern,
                    GrepOption* options);
int pattern_from_file(const char* filename, const char* pattern,
                    GrepOption* options);
int only_match(const char* filename, const char* pattern,
                    GrepOption* options);
int pattern(const char* filename, const char* pattern,
                    GrepOption* options);

#endif