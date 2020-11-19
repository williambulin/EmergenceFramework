#include <iostream>

#include "GameHost.hpp"
#include "Game.hpp"
#include "Log/Logger.hpp"
#include "Math.hpp"
#include "Window/GLFW.hpp"

class GameDemo final : public Game {
private:
  std::unique_ptr<Window::GLFW> m_window{nullptr};

private:
  [[nodiscard]] bool update(float) final {
    m_window->processMessages();
    return true;
  }

public:
  GameDemo(int argc = 0, char **argv = nullptr, char **env = nullptr) : Game{argc, argv, env} {
    m_window = std::make_unique<Window::GLFW>();
  }

  ~GameDemo() final {}
};

int main(int argc, char **argv, char **env) {
  return GameHost::run<GameDemo>(argc, argv, env);
}
