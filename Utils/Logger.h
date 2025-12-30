#ifndef LOGGER_H
#define LOGGER_H

namespace MythicalRuins {

    enum LogLevel {
        Debug = 0,
        Info = 1,
        Warning = 2,
        Error = 3,
        Critical = 4
    };

    class Logger {
    public:
        static void setLogLevel(LogLevel level);

        static void Log(const char* message, LogLevel level);
        static void logDebug(const char* message);
        static void logInfo(const char* message);
        static void logWarning(const char* message);
        static void logError(const char* message);
        static void logCritical(const char* message);

    private:
        static LogLevel m_logLevel;
    };

} // MythicalRuins

#endif //LOGGER_H
