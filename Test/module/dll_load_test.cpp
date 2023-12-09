

#include "utilities/filesystem.hpp"
#include "utilities/dll/loader.hpp"
#include "utilities/logger/logger.hpp"
#include <catch2/catch.hpp>
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>

TEST_CASE("DLL Load Test", "[dll]")
{
    using namespace nitros;

    utils::setup_logger({ std::make_shared<spdlog::sinks::stdout_color_sink_mt>() })->set_level(spdlog::level::debug);

#if defined(PLATFORM_WINDOWS)
    auto sample_dll_path = std::filesystem::path{ "SampleDll.dll" };
    auto dll_lib = utils::dll::load_dll(sample_dll_path, {utils::dll::load_mode::active});
#else
    auto dll_lib = utils::dll::load_dll("../lib/libSampleDll.so", {utils::dll::load_mode::active});
#endif
    REQUIRE(dll_lib);

    auto v_func =  dll_lib->get_fnc_obj<std::int32_t()>("get_v");

    REQUIRE( v_func() == 5);
}