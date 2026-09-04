#ifndef N01Z_DEBUG_H
#define N01Z_DEBUG_H

#include <iostream>

namespace debug
{
    inline void log(const char *const logMessage)
    {
        std::cout << logMessage << std::endl;
        // todo: log file implementation
    }

    inline void err(const char *const errMessage)
    {
        std::cout << "ERROR: " << errMessage << std::endl;
        // todo: log file implementation
    }
}

#endif //N01Z_DEBUG_H
