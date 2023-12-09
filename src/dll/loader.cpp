

#include "./dll_loader.hpp"
#include "utilities/dll/loader.hpp"

namespace nitros::utils::dll
{
    auto IDllLib::has_symbol(std::string_view  name) const -> bool
    {
        if(auto ptr = get_dll_sym(name)) {
            return true;
        }
        else {
            return false;
        }
    }

    /**
     * @returns DllLib Ptr, Check for Empty obj
     * */
    auto load_dll(const utils::fs::path  &lib_path, std::initializer_list<load_mode> modes ) -> utils::Uptr<IDllLib>
    {
        if(utils::fs::exists(lib_path)) 
        {
            auto mode = std::uint32_t{};

            for(auto&& mode_ : modes) {
                switch (mode_)
                {
                    case load_mode::lazy : mode |= RTLD_LAZY;  break;
                    case load_mode::active : mode |= RTLD_NOW; break;
                }
            }

            auto lib_f = dlopen(lib_path.c_str(), mode);
            if(lib_f == NULL) {
                print_error();
                return {};
            }

            return std::make_unique<DllLib>( lib_f, lib_path, lib_path.c_str() );
        }
        return {};
    }
} // namespace nitros::dll
