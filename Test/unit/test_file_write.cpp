
#include <catch2/catch.hpp>
#include "utilities/files/files.hpp"
#include "utilities/filesystem.hpp"

TEST_CASE("File Write Test", "[file system]")
{
    using namespace nitros;

    auto bin_vec = std::vector<std::uint8_t>{};
    for(auto i = 0; i < 500; i++)
    {
        bin_vec.push_back( i % 256 );
    };

    utils::writer::write_binary( "Sample_bin", { static_cast<const std::uint8_t*>( bin_vec.data() ), bin_vec.size() } );

    auto bin_vec2 = utils::reader::read_binary("Sample_bin");

    REQUIRE( bin_vec == bin_vec2 );


    struct SamplePOD
    {
        std::uint32_t   a;
        float           b;
        char            c;
    };

    auto pod = SamplePOD{};
    pod.a = 5;
    pod.b = 6.f;
    pod.c = 'c';

    utils::writer::write_binary("Sample_bin_2", { reinterpret_cast<const std::uint8_t*>(&pod), sizeof(pod) });

    auto pod_bin = utils::reader::read_binary("Sample_bin_2");
    auto pod_2 = SamplePOD{};

    std::memcpy( &pod_2, &pod, sizeof(pod) );

    REQUIRE( pod_2.a == pod.a );
    REQUIRE( pod_2.b == pod.b );
    REQUIRE( pod_2.c == pod.c );
}