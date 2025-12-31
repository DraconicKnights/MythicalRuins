#ifndef LOGGER_H
#define LOGGER_H

#include <functional>
#include <string_view>

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
        using Sink = std::function<void(const char* message, LogLevel levle)>;

        static void setLogLevel(LogLevel level);

        static void AddSink(Sink sink);
        static void ClearSinks();

        static void Log(const char* message, LogLevel level);
        static void logDebug(const char* message);
        static void logInfo(const char* message);
        static void logWarning(const char* message);
        static void logError(const char* message);
        static void logCritical(const char* message);

    private:
        static LogLevel m_logLevel;
        static std::vector<Sink> m_Sinks;
    };

} // MythicalRuins

#endif //LOGGER_H
