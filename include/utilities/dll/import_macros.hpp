

#ifndef NITROS_DLL_CONFIG_HPP
#define NITROS_DLL_CONFIG_HPP

#if defined(WIN32)
    #define DLL_EXPORT_ST  __declspec(dllexport)
#else
    #define DLL_EXPORT_ST
#endif

#define NITROS_DLL_FUNC(f_name, y)  extern "C"  {  DLL_EXPORT_ST auto f_name() -> void* { return reinterpret_cast<void*>( y ); } }

#endif