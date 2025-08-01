#include "Crash.h"

#include <stdlib.h>
#include <ogc/system.h>
#include <grrlib.h>

#include <string_view>

void crash(int exit_code, const std::source_location location)
{
    const std::string_view file_name{location.file_name()};
    size_t last_slash_index = file_name.find_last_of("/");

    std::string_view file_basename{};
    if (last_slash_index != file_name.npos) {
        file_basename = file_name.substr(last_slash_index + 1);
    }
    else {
        file_basename = file_name;
    }

    SYS_Report("Crash code: %d\n", exit_code);
    SYS_Report("Source: %s:%lu:%lu\n", file_basename.data(), location.line(), location.column());

    GRRLIB_Exit();
    exit(exit_code);
}
