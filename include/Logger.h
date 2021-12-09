#ifndef LOGGER_H
#define LOGGER_H
#include <cstdio>
#include <cstdarg>
#include <mutex>
#include <thread>
#include <iostream>

extern std::mutex m;    

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
        std::unique_lock<std::mutex> lk(m);
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "[thread " << std::hex << this_id << "] " << std::flush;
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
