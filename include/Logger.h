#ifndef LOGGER_H
#define LOGGER_H
#include <cstdio>
#include <cstdarg>
#include <thread>

class Logger {
public:
    static Logger *get_logger() {
        static Logger l;
        return &l;
    }

    void log(const char *format, ...) {
        va_list argptr;
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        va_end(argptr);
    }

    void debug(const char *format, ...) {
        va_list argptr; 
        va_start(argptr, format);
        vfprintf(stderr, format, argptr);
        va_end(argptr);
    }

private:
    Logger() = default;
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
};

#endif // LOGGER_H
