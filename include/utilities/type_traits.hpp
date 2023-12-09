

#ifndef UTILS_TYPE_TRAITS_HPP
#define UTILS_TYPE_TRAITS_HPP

#include <type_traits>
#if defined(__GNUC__) || defined(__clang__)
#include <experimental/type_traits>
#endif

namespace nitros::utils
{
#if defined(_MSC_VER)
    namespace internal 
    {
      struct nonesuch {
          ~nonesuch() = delete;
          nonesuch(nonesuch const&) = delete;
          void operator=(nonesuch const&) = delete;
      };

        template <class Default, class AlwaysVoid, template<class...> class Op, class... Args>
        struct detector {
          using value_t = std::false_type;
          using type = Default;
        }; 

        template <class Default, template<class...> class Op, class... Args>
        struct detector<Default, std::void_t<Op<Args...>>, Op, Args...> {
          using value_t = std::true_type;
          using type = Op<Args...>;
        };
    }

    template <template<class...> class Op, class... Args>
    using is_detected = typename internal::detector<internal::nonesuch, void, Op, Args...>::value_t;
    template <template<class...> class Op, class... Args>
    using is_detected_t = typename internal::detector<internal::nonesuch, void, Op, Args...>::type;

    template< template<class...> class Op, class... Args >
    constexpr inline bool is_detected_v = is_detected<Op, Args...>::value;

#elif defined(__GNUC__) || defined(__clang__)
    template <template<class...> class Op, class... Args>
    using is_detected = std::experimental::is_detected<Op, Args ... >;
    template <template<class...> class Op, class... Args>
    using is_detected_t = std::experimental::detected_t<Op, Args ...>;
    template< template<class...> class Op, class... Args >
    constexpr inline bool is_detected_v = is_detected<Op, Args...>::value;
#endif

} // namespace nitros::utils

#endif