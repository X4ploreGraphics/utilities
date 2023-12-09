

#ifndef NITROS_DLL_IMPL_LOADER_HPP
#define NITROS_DLL_IMPL_LOADER_HPP

#include "utilities/dll/loader.hpp"
#include "../logger/log.hpp"
#include <gsl/gsl>
#include <cassert>
#include <dlfcn.h>
#include <iostream>

namespace nitros::utils::dll
{
    inline void print_error() {
        for(char* cer = dlerror(); cer != NULL; cer = dlerror())
        {
            utils::log::Logger()->error(cer);
        }
    }

    class DllLib : public IDllLib
    {
        public:
        explicit DllLib(void* dll_handle, const utils::fs::path  &path_, std::string_view  name)
            :_dll_handle{dll_handle}
            ,_path{path_}
            ,_name{name}
        {
            Expects(dll_handle);
        }

        ~DllLib()
        {
            dlclose(_dll_handle);
        }

        auto full_path() -> utils::fs::path final {
            return _path;
        }

        auto name() -> std::string final {
            return _name;
        }

        protected:

        auto get_dll_sym(std::string_view  func_name) const -> void* final
        {
            auto sym_h = dlsym(_dll_handle, func_name.data());
            if(sym_h == NULL) {
                print_error();
                return nullptr;
            }
            return sym_h;
        }


        void*           _dll_handle;
        utils::fs::path _path;
        std::string     _name;
    };
} // namespace nitros::dll


#endif