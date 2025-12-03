#include "options.h"

// -s Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах.

void handle_s_flag(GrepOptions* options) { options->silent_mode = 1; }