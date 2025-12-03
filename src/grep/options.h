#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdio.h>

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
    int ignore_case;         // Флаг -i
    int invert_match;        // Флаг -v
    int count_only;          // Флаг -c
    int files_with_matches;  // Флаг -l
    int line_number;         // Флаг -n
    int no_filename;         // Флаг -h
    int silent_mode;         // Флаг -s
    int pattern_from_file;   // Флаг -f
    int only_matching;       // Флаг -o
    int pattern_flag;        // Флаг -e
    int file_count;          // Количество обрабатываемых файлов

    char** patterns;
    int pattern_count;
} GrepOptions;

// Для инициализации и очистки от опций
void initialize_options(GrepOptions* options);
void cleanup_options(GrepOptions* options);

// Обработка аргументов
int process_arguments(GrepOptions* options, int argc, char** argv);
int validate_patterns(GrepOptions* options);

// Чтение файлов
void file_read_grep(const char* filename, GrepOptions* options);

// Функции для флагов
void handle_e_flag(GrepOptions* options, const char* optarg);
void handle_i_flag(GrepOptions* options);
void handle_v_flag(GrepOptions* options);
void handle_c_flag(GrepOptions* options);
void handle_l_flag(GrepOptions* options);
void handle_n_flag(GrepOptions* options);
void handle_h_flag(GrepOptions* options);
void handle_s_flag(GrepOptions* options);
void handle_f_flag(GrepOptions* options, const char* optarg);
void handle_o_flag(GrepOptions* options);

// Вспомогательные функции
void add_pattern(GrepOptions* options, const char* pattern);
int is_match(const char* line, GrepOptions* options);
void print_line(const char* filename, int line_num, const char* line,
                GrepOptions* options);
void print_only_matches(const char* filename, int line_num, const char* line,
                        GrepOptions* options);
void print_count(const char* filename, int count, GrepOptions* options);
void print_filename(const char* filename, GrepOptions* options);
char* my_strcasestr(const char* haystack, const char* needle);

#endif