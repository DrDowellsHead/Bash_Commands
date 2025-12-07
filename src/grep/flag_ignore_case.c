#include <ctype.h>
#include <string.h>

#include "options.h"

// -i — ищем строку без учета регистра в указанном файле. Например, найдем
// строки с  UNIX, Unix, unix командой: grep -i "UNix" geekfile.txt.

void handle_i_flag(GrepOptions* options) { options->ignore_case = 1; }