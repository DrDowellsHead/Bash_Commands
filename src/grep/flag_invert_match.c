#include "options.h"

// -v Выдаёт все строки, за исключением содержащих образец.

void handle_v_flag(GrepOptions* options) { options->invert_match = 1; }