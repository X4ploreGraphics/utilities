

#ifndef NITROS_UITLS_MEMORY_HPP
#define NITROS_UITLS_MEMORY_HPP

#include <memory>

namespace nitros::utils
{
    template <typename _Tp>
    using Sptr = std::shared_ptr<_Tp>;

    template <typename _Tp>
    using Wptr = std::weak_ptr<_Tp>;

    template <typename _Tp, typename Deleter = std::default_delete<_Tp>>
    using Uptr = std::unique_ptr<_Tp, Deleter>;

}

#endif