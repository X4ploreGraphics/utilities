

#include "observable.hpp"

namespace nitros::utils
{
    template <typename T, template <typename _Tp, typename ... > typename container_, typename... Args>
    void Observable<T, container_, Args ...>::add(const observer_handle &observer) {
        _observers.push_back(observer);
    }

    template <typename T, template <typename _Tp, typename ... > typename container_, typename... Args>
    void Observable<T, container_, Args ...>::remove(const observer_handle &observer) {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
    }

    template <typename T, template <typename _Tp, typename ... > typename container_, typename... Args>
    void Observable<T, container_, Args ...>::notify(Args &&... args) {
        for (auto &observer : _observers) {
            std::invoke(observer, std::forward<Args>(args)...);
        }
    }
} // namespace nitros::utils
