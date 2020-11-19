#include "Thread.hpp"
#include "Platform.hpp"

#if defined(OS_WINDOWS)
#include <Windows.h>
#endif

void Thread::Thread::kill() {
  auto threadHandle{native_handle()};

#if defined(OS_WINDOWS)
  TerminateThread(threadHandle, 1);
#else
  pthread_cancel(threadHandle);
#endif

  join();
}
