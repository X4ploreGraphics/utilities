

#include "utilities/chrono/chrono.hpp"

int main(int argc, char const *argv[])
{
    using namespace nitros::utils::chrono;

    constexpr auto f1 = 10_kHz;
    constexpr auto f2 = f1 * 4;
    constexpr auto f3 = 4 * f1;

    static_assert( f1.count() == 10 );
    static_assert( f2.count() == 4 * 10 );

    constexpr auto duration  = get_duration<std::chrono::microseconds>(f1);
    constexpr auto f4 = get_frequency<kiloHertz>(duration);

    static_assert(duration.count() == 100);
    static_assert(f4.count() == f1.count());

    constexpr auto f5 = frequency_cast<Hertz>(f1);
    static_assert(f5.count() == 10'000);

    return EXIT_SUCCESS;
}
