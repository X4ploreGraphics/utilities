

#include <catch2/catch.hpp>
#include "utilities/filesystem.hpp"

TEST_CASE("File System Test", "[file system]")
{
    using namespace nitros;

    REQUIRE( utils::fs::create_directory("UtilFile") );
    REQUIRE( utils::fs::exists("UtilFile") );
}