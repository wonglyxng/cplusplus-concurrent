//
// Created by wlx on 2021/1/3.
//

#include <vector>

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Logger.h"

static const std::string LOGGER_NAME = "common-logger";
static const std::string LOGGER_FILE_NAME = "debug.log";
static const std::string LOGGER_CONSOLE_PATTERN = "[%m-%d %H:%M:%S.%e][%^%L%$]  %v";
static const std::string LOGGER_FILE_PATTERN = "[%Y-%m-%d %H:%M:%S.%e] [%^%5l%$]  %v";

Logger::Logger() {
    init();
}

Logger::~Logger() {
    spdlog::drop_all();
}

void Logger::init() {
    std::vector<spdlog::sink_ptr> sinks;
#ifdef _DEBUG
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_level(spdlog::level::debug);
    consoleSink->set_pattern(LOGGER_CONSOLE_PATTERN);
    sinks.push_back(consoleSink);
#endif
    auto dailySink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(LOGGER_FILE_NAME, 0, 0);
    dailySink->set_level(spdlog::level::debug);
    dailySink->set_pattern(LOGGER_FILE_PATTERN);
    sinks.push_back(dailySink);
    logger_ = std::make_shared<spdlog::logger>(LOGGER_NAME, std::begin(sinks), std::end(sinks));
    //register it if you need to access it globally
    spdlog::register_logger(logger_);

    // 设置日志记录级别
#ifdef _DEBUG
    logger_->set_level(spdlog::level::trace);
#else
    logger_->set_level(spdlog::level::err);
#endif
    //设置当出发 err 或更严重的错误时立刻刷新日志到  disk
    logger_->flush_on(spdlog::level::err);
    spdlog::flush_every(std::chrono::seconds(3));
}

