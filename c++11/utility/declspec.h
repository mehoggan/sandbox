#pragma once

// Define import/export macro for public symbols
#ifdef UTILITY_LIBRARY_DYNAMIC

  #if defined(__gnu_linux__) || defined(__linux__)
    #define UTILITY_DECL_EXPORT __attribute__((visibility("default")))
    #define UTILITY_DECL_IMPORT __attribute__((visibility("default")))
  #elif defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
    #define UTILITY_DECL_EXPORT __declspec(dllexport)
    #define UTILITY_DECL_IMPORT __declspec(dllimport)
  #endif

  #ifdef UTILITY_LIBRARY
    #define UTILITY_API UTILITY_DECL_EXPORT
  #else
    #define UTILITY_API UTILITY_DECL_IMPORT
  #endif

#else
#   define UTILITY_API
#endif
