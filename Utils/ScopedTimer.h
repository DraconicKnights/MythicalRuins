#ifndef MYTHICALRUINS_SCOPEDTIMER_H
#define MYTHICALRUINS_SCOPEDTIMER_H

#include <chrono>
#include "Logger.h"

namespace MythicalRuins {
    class ScopedTimer {
    public:
        ScopedTimer(const char* name)
                : m_Name(name), m_Start(std::chrono::high_resolution_clock::now()) {}

        ~ScopedTimer() {
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::milli>(end - m_Start).count();
            std::string msg = std::string(m_Name) + " took " + std::to_string(duration) + " ms";
            Logger::logDebug(msg.c_str());
        }

    private:
        const char* m_Name;
        std::chrono::high_resolution_clock::time_point m_Start;
    };

}

#endif //MYTHICALRUINS_SCOPEDTIMER_H
