#include "Logger.h"
#include <iostream>

MythicalRuins::LogLevel MythicalRuins::Logger::m_logLevel = LogLevel::Info;

void MythicalRuins::Logger::setLogLevel(MythicalRuins::LogLevel level) {
    m_logLevel = level;
}

void MythicalRuins::Logger::Log(const char *message, MythicalRuins::LogLevel level) {
    if (level >= m_logLevel) {
        switch (level) {
            case Debug:
                std::cout << "[DEBUG]: " << message << std::endl;
                break;
            case Info:
                std::cout << "[INFO]: " << message << std::endl;
                break;
            case Warning:
                std::cout << "[WARNING]: " << message << std::endl;
                break;
            case Error:
                std::cout << "[ERROR]: " << message << std::endl;
                break;
            case Critical:
                std::cout << "[CRITICAL]: " << message << std::endl;
                break;
            default:
                std::cout << "[UNKNOWN]: " << message << std::endl;
                break;
        }
    }
}

void MythicalRuins::Logger::logDebug(const char* message) {
    Log(message, Debug);
}
void MythicalRuins::Logger::logInfo(const char* message) {
    Log(message, Info);
}
void MythicalRuins::Logger::logWarning(const char* message) {
    Log(message, Warning);
}
void MythicalRuins::Logger::logError(const char* message) {
    Log(message, Error);
}
void MythicalRuins::Logger::logCritical(const char* message) {
    Log(message, Critical);
}