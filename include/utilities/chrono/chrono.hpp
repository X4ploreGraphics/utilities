

#ifndef  NITROS_UTILS_CHRONO_HPP
#define  NITROS_UTILS_CHRONO_HPP

#include <chrono>
#include <gsl/gsl>

namespace nitros::utils
{
    namespace chrono
    {

        template <typename rep, typename period>
        using duration = std::chrono::duration<rep, period>;

        template <typename _Rep, typename _Period = std::ratio<1, 1>>
        struct frequency
        {
            using rep = _Rep;
            using period = _Period;

            static_assert(std::is_arithmetic_v<rep>);

            constexpr frequency() = default;
            constexpr frequency(rep value)
                :_value{value}
            {}

            constexpr auto count() const noexcept -> rep{
                return _value;    
            }

            template <typename Scalar>
            friend constexpr auto operator*(Scalar scalar, frequency  freq) {
                return frequency{freq.count() * scalar};
            }

            template <typename Scalar>
            friend constexpr auto operator*(frequency  freq, Scalar scalar) {
                return frequency{freq.count() * scalar};
            }

            template <typename Scalar>
            friend constexpr auto operator/(Scalar scalar, frequency  freq) {
                return frequency{freq.count() / scalar};
            }

            template <typename Scalar>
            friend constexpr auto operator/(frequency  freq, Scalar scalar) {
                return frequency{freq.count() / scalar};
            }

            private:
            rep  _value{};
        };

        using Hertz = frequency<std::int64_t>;
        using kiloHertz = frequency<std::int64_t, std::kilo>;
        using megaHertz = frequency<std::int64_t, std::mega>;
        using gigaHertz = frequency<std::int64_t, std::giga>;
        using teraHertz = frequency<std::int64_t, std::tera>;
        using petaHertz = frequency<std::int64_t, std::peta>;
        using exaHertz  = frequency<std::int64_t, std::exa>;

        template <typename duration_type, typename Rep, typename Period>
        [[nodiscard]] constexpr auto get_duration(const frequency<Rep, Period> &value) {
            using d_period = typename duration_type::period;
            using d_rep = typename duration_type::rep;

            constexpr auto d_num = d_period::num;
            constexpr auto d_den = d_period::den;

            constexpr auto f_num = Period::num;
            constexpr auto f_den = Period::den;

            d_rep count = gsl::narrow_cast<d_rep>(d_den * f_den)/(value.count() * f_num * d_num);
            return duration_type{ count };
        }

        template <typename frequency_type, typename Rep, typename Period>
        [[nodiscard]] constexpr auto get_frequency(const std::chrono::duration<Rep, Period> &value) {
            using d_period = typename frequency_type::period;
            using d_rep = typename frequency_type::rep;

            constexpr auto d_num = d_period::num;
            constexpr auto d_den = d_period::den;

            constexpr auto f_num = Period::num;
            constexpr auto f_den = Period::den;

            d_rep count = gsl::narrow_cast<d_rep>(d_den * f_den)/(value.count() * f_num * d_num);
            return frequency_type{ count };
        }

        template <typename freq_type, typename Rep, typename Period>
        [[nodiscard]] constexpr auto frequency_cast(const frequency<Rep, Period> &value) {
            using d_period = typename freq_type::period;
            using d_rep    = typename freq_type::rep;

            constexpr auto d_num = d_period::num;
            constexpr auto d_den = d_period::den;

            constexpr auto f_num = Period::num;
            constexpr auto f_den = Period::den;

            d_rep count = gsl::narrow_cast<d_rep>(value.count() * f_num * d_den)/(f_den * d_num);
            return freq_type{ count };
        }   

        inline namespace literals
        {
            constexpr auto operator""_XHz(unsigned long long value) -> exaHertz{
                return {gsl::narrow_cast<std::int64_t>(value)};
            }

            constexpr auto operator""_PHz(unsigned long long value) -> petaHertz{
                return {gsl::narrow_cast<std::int64_t>(value)};
            }

            constexpr auto operator""_GHz(unsigned long long value) -> gigaHertz{
                return {gsl::narrow_cast<std::int64_t>(value)};
            }

            constexpr auto operator""_MHz(unsigned long long value) -> megaHertz{
                return {gsl::narrow_cast<std::int64_t>(value)};
            }

            constexpr auto operator""_kHz(unsigned long long value) -> kiloHertz{
                return {gsl::narrow_cast<std::int64_t>(value)};
            }

            constexpr auto operator""_Hz(unsigned long long value) -> Hertz{
                return {gsl::narrow_cast<std::int64_t>(value)};
            }

            //---------------------------------------------------------------

            constexpr auto operator""_XHz(long double value) -> frequency<long double, std::exa> {
                return {value};
            }

            constexpr auto operator""_PHz(long double value) -> frequency<long double, std::peta> {
                return {value};
            }

            constexpr auto operator""_GHz(long double value) -> frequency<long double, std::giga> {
                return {value};
            }

            constexpr auto operator""_MHz(long double value) -> frequency<long double, std::mega> {
                return {value};
            }

            constexpr auto operator""_kHz(long double value) -> frequency<long double, std::kilo>{
                return {value};
            }

            constexpr auto operator""_Hz(long double value) -> frequency<long double>{
                return {value};
            }
        }
    }
} // namespace nitros::utils

#endif