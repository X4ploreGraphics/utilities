#include <iostream>

auto get_value() -> std::int32_t
{
    return 5;
}

extern "C" 
{
    __declspec(dllexport) auto get_v() -> void* {
        return reinterpret_cast<void*>( get_value );
    }
}