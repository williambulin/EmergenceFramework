#include "Logger.hpp"

#include <chrono>
#include <ctime>

[[nodiscard]] auto Log::Logger::operator()(Level level) -> std::ostream & {
  std::ostream &out{std::cerr};
  auto          time{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
  std::string timeString{std::ctime(std::addressof(time))};
#pragma clang diagnostic pop

  auto timeStringView{std::string_view{timeString}};
  timeStringView.remove_suffix(1);

  out << "[" + std::string{timeStringView} + "][" << m_levelToString[level] << "] ";
  return out;
}
