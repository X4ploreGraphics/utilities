

#ifndef UTILS_FIXED_VEC_HPP
#define UTILS_FIXED_VEC_HPP

#include "utilities/type_traits.hpp"
#include "utilities/algorithm.hpp"
#include <cstdint>
#include <type_traits>
#include <array>

namespace nitros::utils
{
    namespace internal 
    {
        template <typename T>
        using equality_trait = decltype(std::declval<T>() == std::declval<T>());
        template <typename T>
        using lesser_trait = decltype(std::declval<T>() < std::declval<T>());
        template <typename T>
        inline constexpr auto always_false = false;
    }

    template<typename T, std::size_t heap_size_>
    class FixedSizeVec;
    template <typename value_type, std::size_t heap_size_>
    constexpr auto operator==(const FixedSizeVec<value_type, heap_size_> &lhs, const FixedSizeVec<value_type, heap_size_>  &rhs) -> bool ;
    

    template<typename T, std::size_t heap_size_>
    class FixedSizeVec
    {
        public:
        using value_type = T;
        using reference_type = std::add_lvalue_reference_t<value_type>;
        using iterator = std::add_pointer_t<value_type>;
        using const_iterator = std::add_pointer_t< std::add_const_t<value_type> >;

        constexpr explicit FixedSizeVec() noexcept = default;
        constexpr FixedSizeVec(std::initializer_list<value_type>  values)
            :_data{}
            ,_size{values.size()}
        {
            auto it1 = values.begin();
            auto it2 = _data.begin();

            for( ; it1 != values.end() ; ++it1, ++it2) {
                *it2 = *it1;
            }
        }

        constexpr auto max_capacity() const noexcept -> std::size_t {
            return _data.max_size();
        }

        constexpr auto data() noexcept -> value_type* {
            return _data.data();
        }

        constexpr auto data() const noexcept -> const value_type* {
            return _data.data();
        }

        constexpr auto size() const noexcept -> std::size_t {
            return _size;
        }

        constexpr auto begin() noexcept -> iterator {
            return iterator{_data.data()};
        }

        constexpr auto begin() const noexcept -> const_iterator {
            return const_iterator{_data.data()};
        }

        constexpr auto end() noexcept -> iterator {
            return iterator{_data.data() + _size};
        }

        constexpr auto end() const noexcept -> const_iterator {
            return const_iterator{_data.data() + _size};
        }

        constexpr auto at(const std::size_t  &index) noexcept -> value_type& {
            return _data.at(index);
        }

        constexpr auto at(const std::size_t  &index) const noexcept -> const value_type& {
            return _data.at(index);
        }

        constexpr auto operator[](const std::size_t  &index) noexcept -> value_type& {
            return _data[index];
        }

        constexpr auto operator[](const std::size_t  &index) const noexcept -> const value_type& {
            return _data[index];
        }

        constexpr auto push_back(const value_type &v) -> reference_type {
            return _data[_size++] = v;
        }

        constexpr auto push_back(value_type &&v) -> reference_type {
            return _data[_size++] = std::move(v);
        }

        friend constexpr auto operator== <>(const FixedSizeVec<value_type, heap_size_> &lhs, const FixedSizeVec<value_type, heap_size_>  &rhs) -> bool; 
        
        private:
        std::array<T, heap_size_>   _data;
        std::size_t     _size;
    };

    template <typename value_type, std::size_t heap_size_>
    constexpr auto operator==(const FixedSizeVec<value_type, heap_size_> &lhs, const FixedSizeVec<value_type, heap_size_>  &rhs) -> bool 
    {   
        if(lhs.size() != rhs.size()) {
            return false;
        }
        if constexpr( is_detected_v<internal::equality_trait, value_type> ) 
        {
            auto it1 = lhs.begin();
            auto it2 = rhs.begin();
            for( ; it1 != lhs.end()  ; ++it1, ++it2) {
                if(! (*it1 == *it2) ) {
                    return false;
                }
            }
            return true;
        }
        else if constexpr( is_detected_v<internal::lesser_trait, value_type> ) {
            return !lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) &&
                    !lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
        }
        else {
            static_assert( internal::always_false<value_type>, "Operator== not found" );
        }
    }

} // namespace nitros::utils

#endif