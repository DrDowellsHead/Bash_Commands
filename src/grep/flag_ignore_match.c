#include "options.h"

// -v — находим строки, которые не соответствуют указанному шаблону строки
// поиска: grep -v "unix" geekfile.txt.

void handle_v_flag(GrepOptions* options) { options->invert_match = 1; }