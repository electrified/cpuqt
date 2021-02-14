#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

void configureLoggers() {
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  console_sink->set_level(spdlog::level::debug);

  auto processor_logger = std::make_shared<spdlog::logger>("processor", console_sink);
  processor_logger->set_level(spdlog::level::critical);

  auto general_logger = std::make_shared<spdlog::logger>("general", console_sink);
  general_logger->set_level(spdlog::level::debug);

  auto console_logger = std::make_shared<spdlog::logger>("console", console_sink);
  console_logger->set_level(spdlog::level::debug);

  spdlog::register_logger(processor_logger);
  spdlog::register_logger(general_logger);
  spdlog::register_logger(console_logger);
}