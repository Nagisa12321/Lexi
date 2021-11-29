#include <cstdlib>
#include <iostream>

#include "Utils.h"
#include "Logger.h"

void lexi_abort(const char *info) {
    Logger::get_logger()->log(info);
    std::abort();
}
