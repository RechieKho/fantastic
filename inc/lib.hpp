#ifndef LIB_HPP
#define LIB_HPP

#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
    #define PLATFORM_MACOS
#elif defined(__linux__)
    #define PLATFORM_LINUX
#else
    #error "Unsupported platform"  
#endif

namespace LIBRARY_NAME { }

#endif // LIB_HPP