#ifndef OPTIONS_H
#define OPTIONS_H

// Структура для работы с флагами команды cat
typedef struct {
    int numbering_non_empty;  // flag b
    int symbols_end_line;     // flag e
    int numbering_all_str;    // flag n
    int compession_str;       // flag s
    int view_tabs;            // flag t
} CatOption;

void file_read(const char *filename, CatOption *options);
int numbering_non_empty(char *line, CatOption *options, int *line_number);
int symbols_end_line(char *line, CatOption *options);
int numbering_all_str(char *line, CatOption *options, int *line_number);
int compession_str(char *line, CatOption *options, int *last_empty);
int view_tabs(char *line, CatOption *options);

#endif