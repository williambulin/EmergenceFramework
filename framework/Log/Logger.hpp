#pragma once

#include "SharedLibrary.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <map>

namespace Log {
  class Logger;
}

class shared Log::Logger final {
public:
  enum class Level : std::uint8_t {
    Debug,
    Info,
    Warning,
    Error,
  };

  std::map<Level, std::string> m_levelToString{
  {Level::Debug, "Debug"},
  {Level::Info, "Info"},
  {Level::Warning, "Warning"},
  {Level::Error, "Error"},
  };

public:
  explicit Logger()      = default;
  Logger(Logger const &) = delete;
  ~Logger()              = default;

  Logger &operator=(Logger const &) = delete;

  [[nodiscard]] auto operator()(Level level = Level::Debug) -> std::ostream &;
};
