#pragma once

#include "Platform.hpp"

#if defined SHARED_LIBRARY_EXPORT

#if defined OS_WINDOWS
#define shared __declspec(dllexport)
#elif defined OS_MACOS || defined OS_LINUX
#define shared __attribute__((visibility("default")))
#endif

#elif defined SHARED_LIBRARY_IMPORT

#if defined OS_WINDOWS
#define shared __declspec(dllimport)
#else
#define shared
#endif

#else

#define shared
#warning No library type defined, potentially unwanted behavior

#endif
