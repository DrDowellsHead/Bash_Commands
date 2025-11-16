#ifdef OPTIONS_H
#define OPTIONS_H

// Структура для работы с флагами команды cat
typedef struct {
  int numbering_non_empty;  // flag b
  int symbols_end_line;     // flag e
  int numbering_all_str;    // flag n
  int compession_str;       // flag s
  int view_tabs;            // flag t
} CatOption;

#endif