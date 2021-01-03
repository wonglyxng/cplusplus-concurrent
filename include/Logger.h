//
// Created by wlx on 2021/1/3.
//

#ifndef CPLUSPLUS_CONCURRENT_LOGGER_H
#define CPLUSPLUS_CONCURRENT_LOGGER_H

#include <memory>

#ifndef SPDLOG_TRACE_ON
#define SPDLOG_TRACE_ON
#endif

#ifndef SPDLOG_DEBUG_ON
#define SPDLOG_DEBUG_ON
#endif

#include <spdlog/spdlog.h>

#ifdef _WIN32
#define __FILENAME__ (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1):__FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#endif

#ifndef SUFFIX
#define SUFFIX(msg)  std::string(msg).append("  //")\
        .append(__FILENAME__).append(":").append(__func__)\
        .append("()#").append(std::to_string(__LINE__))\
        .append(".").c_str()
#endif

class Logger {
public:
    static Logger &GetLogger() {
        static Logger logger;
        return logger;
    }

    Logger(const Logger &) = delete;

    Logger &operator=(const Logger &) = delete;

    template<typename FormatString, typename... Args>
    void trace(const FormatString &fmt, Args &&...args);

    template<typename FormatString, typename... Args>
    void debug(const FormatString &fmt, Args &&...args);

    template<typename FormatString, typename... Args>
    void info(const FormatString &fmt, Args &&...args);

    template<typename FormatString, typename... Args>
    void warn(const FormatString &fmt, Args &&...args);

    template<typename FormatString, typename... Args>
    void error(const FormatString &fmt, Args &&...args);

    template<typename T>
    void trace(const T &msg);

    template<typename T>
    void debug(const T &msg);

    template<typename T>
    void info(const T &msg);

    template<typename T>
    void warn(const T &msg);

    template<typename T>
    void error(const T &msg);


private:
    Logger();

    ~Logger();

    void init();

private:
    std::shared_ptr<spdlog::logger> logger_;

};


template<typename FormatString, typename... Args>
void Logger::trace(const FormatString &fmt, Args &&... args) {
    logger_->template trace(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Logger::debug(const FormatString &fmt, Args &&... args) {
    logger_->template debug(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Logger::info(const FormatString &fmt, Args &&... args) {
    logger_->template info(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Logger::warn(const FormatString &fmt, Args &&... args) {
    logger_->template warn(fmt, std::forward<Args>(args)...);
}

template<typename FormatString, typename... Args>
void Logger::error(const FormatString &fmt, Args &&... args) {
    logger_->template error(fmt, std::forward<Args>(args)...);
}

template<typename T>
void Logger::trace(const T &msg) {
    logger_->template trace(msg);
}

template<typename T>
void Logger::debug(const T &msg) {
    logger_->template debug(msg);
}

template<typename T>
void Logger::info(const T &msg) {
    logger_->template info(msg);
}

template<typename T>
void Logger::warn(const T &msg) {
    logger_->template warn(msg);
}

template<typename T>
void Logger::error(const T &msg) {
    logger_->template error(msg);
}

#define LogTrace(msg, ...) Logger::getLogger().trace(SUFFIX(msg), __VA_ARGS__)
#define LogDebug(msg, ...) Logger::getLogger().debug(SUFFIX(msg), __VA_ARGS__)
#define LogError(...) Logger::getLogger().error(__VA_ARGS__)
#define LogWarn(...) Logger::getLogger().warn(__VA_ARGS__)
#define LogInfo(...) Logger::getLogger().info(__VA_ARGS__)

#endif //CPLUSPLUS_CONCURRENT_LOGGER_H
