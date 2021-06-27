#ifndef TREE_LOG_H
#define TREE_LOG_H

#include <android/log.h>

class Log {
public:
    static void log(int priority, const char* message, ...);
};

#define log_info(...) Log::log(ANDROID_LOG_INFO, __VA_ARGS__)
#define log_error(...) Log::log(ANDROID_LOG_ERROR, __VA_ARGS__)
#define log_warning(...) Log::log(ANDROID_LOG_WARN, __VA_ARGS__)

#ifndef NDEBUG
#define log_debug(...) Log::log(ANDROID_LOG_DEBUG, __VA_ARGS__)
#else
#define log_debug(...)
#endif //Debug macro

#endif //TREE_LOG_H
