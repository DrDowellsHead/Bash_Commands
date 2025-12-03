#include "options.h"

// -n — отображаем номер строки файла с совпавшей строкой:
// grep -n "unix" geekfile.txt.

void handle_n_flag(GrepOptions* options) { options->line_number = 1; }