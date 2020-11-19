#pragma once

#if defined SHARED_LIBRARY_EXPORT
#define shared __declspec(dllexport)
#elif defined SHARED_LIBRARY_IMPORT
#define shared __declspec(dllimport)
#else
#define shared
#warning No library type defined, potentially unwanted behavior
#endif
