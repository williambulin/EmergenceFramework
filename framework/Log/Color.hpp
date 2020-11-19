#pragma once

#include <string>
#include <string_view>

namespace Log {
  class Color;
}

class Log::Color final {
public:
  explicit Color(float r, float g, float b);
};
