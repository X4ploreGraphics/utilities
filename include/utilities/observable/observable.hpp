

#ifndef NITROS_UTILS_OBSERVABLE_HPP
#define NITROS_UTILS_OBSERVABLE_HPP

#include <functional>
#include <vector>

namespace nitros::utils
{   
    template <typename T, template <typename _Tp, typename ... > typename container_, typename... Args>
    class Observable
    {
    public:
        using observer_handle = std::function<void(Args &&...)>;

        void add(const observer_handle &observer);
        void remove(const observer_handle &observer);

    private:
        void notify(Args &&... args);

        container_<observer_handle> _observers;
        friend T;
    };

    template <typename T, typename... Args>
    using Observable_Vec = Observable<T, std::vector, Args ...> ;
} // namespace nitros::utils

#include "observable.inl"

#endif