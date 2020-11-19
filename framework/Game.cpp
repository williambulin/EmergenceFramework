#include "Game.hpp"

#include <iostream>

Game::Game(int argc, char **argv, char **env) {
  (void)argc;
  (void)argv;
  (void)env;
}

Game::~Game() {}

int Game::run() {
  while (true) {
    if (!update(0.0f))
      break;  // TODO: Replace with close window
  }
  return 0;
}
