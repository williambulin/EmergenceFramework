#pragma once

#if defined _WIN32 || defined _WIN64
#define OS_WINDOWS
#elif defined __APPLE__
#define OS_MACOS
#else
#define OS_LINUX
#define OS_OTHER
#endif
