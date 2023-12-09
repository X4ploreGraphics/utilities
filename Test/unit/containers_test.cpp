

#include <catch2/catch.hpp>
#include "utilities/containers.hpp"

struct Sample
{
    int a;
    int b;
};

constexpr auto operator==(const Sample &l, const Sample &r) -> bool {
    return l.a == r.a && l.b == r.b;
}

TEST_CASE("Fixed Size Vec", "[containers]")
{
    using namespace nitros::utils;

    auto vec = FixedSizeVec<Sample, 5>{};
    REQUIRE(vec.size() == 0);

    auto s = Sample{.a = 5, .b = 6};
    
    vec.push_back(Sample{});
    vec.push_back(Sample{});

    auto vec2 = FixedSizeVec<Sample, 5>{};
    REQUIRE_FALSE(vec == vec2);

    vec[0] = Sample{.a = 5, .b = 6};
    vec[1] = Sample{.a = 6, .b = 7};

    REQUIRE_FALSE(vec == vec2);

    vec2.push_back(Sample{.a = 5, .b = 6});
    vec2.push_back(Sample{.a = 6, .b = 7});

    REQUIRE(vec == vec2);
}