#include "Log.h"

#include <cstdarg>

void Log::log(int priority, const char *message, ...) {
    va_list argList;
    va_start(argList, message);
    __android_log_vprint(priority, "User log", message, argList);
    __android_log_print(priority, "User log", "\n");
    va_end(argList);
}
