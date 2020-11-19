#pragma once

#include "Platform.hpp"

#if defined OS_WINDOWS
#include <Windows.h>
#endif

#include <memory>
#include <iostream>

namespace GameHost {
  template <class T>
  [[nodiscard]] inline int run(int argc = 0, char **argv = nullptr, char **env = nullptr) {
    try {
      T demo{argc, argv, env};
      return demo.run();
    } catch (std::exception const &e) {
      std::cerr << "An unknown exception has occured: " << e.what() << '\n';
#if defined OS_WINDOWS
      MessageBox(nullptr, e.what(), "An unhandled exception occured", MB_ICONERROR);
#endif
    }
    return 1;
  }
}
