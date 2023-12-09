

#ifndef UTILS_DATA_VECS_HPP
#define UTILS_DATA_VECS_HPP

#include <vector>
#include <array>
#include <cstdint>

namespace nitros::utils
{
    template<std::size_t N>
    using vecf = std::array<float, N>;
    
    template<std::size_t N>
    using veci = std::array<std::int32_t, N>;

    template<std::size_t N>
    using vecUi = std::array<std::uint32_t, N>;

    using vec3f = vecf<3>;
    using vec4f = vecf<4>;
    using vec2f = vecf<2>;
    using vec1f = vecf<1>;

    using vec3i = veci<3>;
    using vec4i = veci<4>;
    using vec2i = veci<2>;
    using vec1i = veci<1>;

    using vec3Ui = vecUi<3>;
    using vec4Ui = vecUi<4>;
    using vec2Ui = vecUi<2>;
    using vec1Ui = vecUi<1>;
} // nitros::utils


#endif // UTILS_DATA_VECS_HPP
