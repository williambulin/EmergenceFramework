#include <iostream>

#include "GameHost.hpp"
#include "Game.hpp"
#include "Log/Logger.hpp"
#include "Math.hpp"
#include "Window/GLFW.hpp"
#include "Renderer/Vulkan/Vulkan.hpp"

class GameDemo final : public Game {
private:
  std::unique_ptr<Window::GLFW>             m_window{nullptr};
  std::unique_ptr<Renderer::Vulkan::Vulkan> m_vulkan{nullptr};

private:
  [[nodiscard]] bool update(float) final;

public:
  GameDemo(int argc = 0, char **argv = nullptr, char **env = nullptr);
  ~GameDemo() final;
};

bool GameDemo::update(float) {
  m_window->processMessages();
  return m_window->isOpen();
}

GameDemo::GameDemo(int argc, char **argv, char **env) : Game{argc, argv, env} {
  std::cout << "GameDemo::GameDemo" << '\n';
  m_window = std::make_unique<Window::GLFW>();
  m_vulkan = std::make_unique<Renderer::Vulkan::Vulkan>(*m_window.get());
}

GameDemo::~GameDemo() {
  std::cout << "GameDemo::~GameDemo" << '\n';
}

int main(int argc, char **argv, char **env) {
  return GameHost::run<GameDemo>(argc, argv, env);
}
