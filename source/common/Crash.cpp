#include "Crash.h"

#include <stdlib.h>
#include <ogc/system.h>

void internal_crash(const char *file, int line, int exit_code)
{
    SYS_Report("Crash code: %d\n", exit_code);
    SYS_Report("Source: %s:%d\n", file, line);

    exit(exit_code);
}
