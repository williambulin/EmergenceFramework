#pragma once

#include <thread>

namespace Thread {
  class Thread;
}

class Thread::Thread : public std::thread {
public:
  template <typename... Ts>
  explicit Thread(Ts &&...args) : std::thread{std::forward<Ts>(args)...} {}
  Thread(Thread const &) = delete;
  ~Thread();

  Thread &operator=(Thread const &) = delete;

  void kill();
};
