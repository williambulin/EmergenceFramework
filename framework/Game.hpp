#pragma once

#include "SharedLibrary.hpp"

class shared Game {
protected:
  explicit Game(int argc = 0, char **argv = nullptr, char **env = nullptr);
  Game(Game const &) = delete;
  virtual ~Game();

  Game &operator=(Game const &) = delete;

  [[nodiscard]] virtual bool update(float delta) = 0;

public:
  [[nodiscard]] int run();
};
