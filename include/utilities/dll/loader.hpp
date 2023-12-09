

#ifndef NITROS_UTILS_DLL_LOADER_HPP
#define NITROS_UTILS_DLL_LOADER_HPP

#include "utilities/utils_export.h"
#include "utilities/filesystem.hpp"
#include "utilities/memory/memory.hpp"
#include <functional>

namespace nitros::utils::dll
{
    enum load_mode {
        lazy, active
    };

    template <typename T>
    struct funct_trait;
    
    template <typename R, typename ... Args>
    struct funct_trait<R(Args ... )>
    {
        using return_type = R;
        using argument_type = std::tuple<Args ...>;
    
        static constexpr std::size_t arg_size = sizeof...(Args);
    };

    class NUTILS_EXPORT IDllLib
    {
        public:
        explicit IDllLib() = default;
        virtual ~IDllLib() = default;

        virtual auto full_path() -> utils::fs::path {
            return {};
        }
        virtual auto name() -> std::string {
            return {};
        }

        auto has_symbol(std::string_view  name) const -> bool;

        private:

        template <typename R, typename tuple_, std::size_t ... I>
        auto _get_fn(void*  ptr_, std::index_sequence<I ...> ) -> std::function<R(std::tuple_element_t<I, tuple_> ... )>
        {
            using func_ptr_t = std::add_pointer_t<R( std::tuple_element_t<I, tuple_> ... )>;

            auto fptr = (void* (*)()) ptr_;
            if constexpr (std::is_same_v<R, void>)
            {
                return std::function<R(std::tuple_element_t<I, tuple_> ... )>{ [ ptr = reinterpret_cast<func_ptr_t>( fptr() )]( std::tuple_element_t<I, tuple_> ... args ) {
                    ptr( args... );
                } };
            }
            else
            {
                return std::function<R(std::tuple_element_t<I, tuple_> ... )>{ [ ptr = reinterpret_cast<func_ptr_t>( fptr() )]( std::tuple_element_t<I, tuple_> ... args ) {
                    return ptr( args... );
                } };
            }
        }

        public:
        

        /**
         * Notes : Prefer get_fn_obj to this function
         * @returns Funct Ptr, check if Funct ptr is empty first
         * */
        template <typename R, typename ... Args>
        auto get_fn_ptr(std::string_view  func_name) -> std::add_pointer_t<R(Args ...)> 
        {
            using func_type = R(Args ...);
            using func_ptr_type = std::add_pointer_t<func_type>;

            auto sym_h = get_dll_sym(func_name);
            if(sym_h == nullptr) {
                return {nullptr};
            }

            auto fpr = (void* (*)()) sym_h;
            return reinterpret_cast<func_ptr_type>( fpr() );
        }

        template <typename Signature>
        auto get_fnc_obj(std::string_view  func_name) -> std::function<Signature>
        {
            using ft =  funct_trait<Signature>;

            auto sym_h = get_dll_sym(func_name);
            if(sym_h == nullptr) {
                return {};
            }

            return _get_fn<typename ft::return_type, typename ft::argument_type>( sym_h, std::make_index_sequence<ft::arg_size>() );
        }

        /**
         * @returns Funct Obj, check if Funct Obj is empty first
         * */
        template <typename R, typename ... Args>
        auto get_fn_obj2(std::string_view  func_name) -> std::function<R(Args ... )>
        {
            using func_type = R(Args ...);
            using func_ptr_type = std::add_pointer_t<func_type>;

            auto sym_h = get_dll_sym(func_name);
            if(sym_h == nullptr) {
                return {};
            }

            auto fpr = (void* (*)()) sym_h;
            if constexpr( std::is_same_v<R, void> )
            {
                return std::function<R(Args ...)>{ [fpr](Args ... args) -> R 
                {    
                    auto fnc = reinterpret_cast<func_ptr_type>( fpr() );
                    fnc( std::forward<Args>(args)... );
                } };
            }
            else
            {
                return std::function<R(Args ...)>{ [fpr](Args ... args) -> R 
                {    
                    auto fnc = reinterpret_cast<func_ptr_type>( fpr() );
                    return fnc( std::forward<Args>(args)... );
                } };
            }
        }

        protected:
        virtual auto get_dll_sym(std::string_view  func_name) const -> void* = 0;
    };

    /**
     * @returns DllLib Ptr, Check for Empty obj
     * */
    NUTILS_EXPORT auto load_dll(const utils::fs::path  &lib_path, std::initializer_list<load_mode> modes ) -> utils::Uptr<IDllLib>;
} // namespace nitros::dll

#endif