

#ifndef  NITROS_UITLS_EXPORT_H
#define  NITROS_UITLS_EXPORT_H

#if defined (WIN32) && !defined(NITROS_UTILS_STATIC)
  #if defined(NitrosUtils_EXPORTS)
    #define  NUTILS_EXPORT __declspec(dllexport)
  #else
    #define  NUTILS_EXPORT __declspec(dllimport)
  #endif 
#else /* defined (WIN32) */
 #define NUTILS_EXPORT
#endif

#ifndef PLATFORMS_DEFINE
#define PLATFORMS_DEFINE

#if defined (WIN32) 
  #define PLATFORM_WINDOWS
#elif defined(__ANDROID__)
  #define PLATFORM_ANDROID
#elif defined(__EMSCRIPTEN__)
  #define PLATFORM_EMSCRIPTEN
#else 
 #define PLATFORM_LINUX
#endif

#endif

#endif