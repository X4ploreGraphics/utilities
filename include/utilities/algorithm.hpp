

#ifndef UTILS_ALGORITHM_HPP
#define UTILS_ALGORITHM_HPP
#include <algorithm>

namespace nitros::utils
{
#if defined(__GNUC__) || defined(__clang__)
    template <typename It1, typename It2>
    inline constexpr auto lexicographical_compare(It1 i_first_, It1 i_last_, It2 o_first_, It2 o_last_) -> bool {
        auto d1 = std::distance(i_first_, i_last_);
        auto d2 = std::distance(o_first_, o_last_);
        if( d1 != d2 ) {
            return d1 < d2;
        }
        auto it1 = i_first_;
        auto it2 = o_first_;
        for(; it1 != i_last_; ++it1, ++it2)
        {
            if( *it1 < *it2 ) {
                return true;
            }
            else if( *it1 > *it2 ) {
                return false;
            }
        }

        return false;
    }
#else
    template <typename It1, typename It2>
    inline constexpr auto lexicographical_compare(It1 i_first_, It1 i_last_, It2 o_first_, It2 o_last_) -> bool {
        return std::lexicographical_compare(i_first_, i_last_, o_first_, o_last_);
    }
#endif
} // namespace nitros::utils;

#endif