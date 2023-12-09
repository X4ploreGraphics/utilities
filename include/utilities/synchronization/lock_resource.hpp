

#ifndef NITROS_UTILS_LOCK_RESOURCE_HPP
#define NITROS_UTILS_LOCK_RESOURCE_HPP

#include "utilities/synchronization/dynamic_semaphore.hpp"
#include "utilities/memory/memory.hpp"
#include <gsl/gsl>

namespace nitros::utils
{
    template <typename T>
    class LockResource
    {
        public:
        class LockAccessor
        {
            public:
            using sem_t = DynamicSemaphore;
            LockAccessor(sem_t  &sem, T  &res)
                :_sem{&sem}
                ,_res{&res}
            {}

            LockAccessor(const LockAccessor &) = delete;
            LockAccessor(LockAccessor &&) = default;

            ~LockAccessor()
            {
                _sem->release();
            }

            auto operator=(const LockAccessor &) -> LockAccessor& = delete;
            auto operator=(LockAccessor &&) -> LockAccessor& = default;

            auto get() noexcept -> T* {
                return _res.get();
            }

            auto get() const noexcept -> const T* {
                return _res.get();
            }

            auto operator->() noexcept -> T* {
                return _res.get();
            }

            auto operator->() const noexcept -> const T* {
                return _res.get();
            }

            auto operator*() noexcept -> T& {
                return *_res;
            }

            auto operator*() const noexcept -> const T& {
                return *_res;
            }

            private:
            gsl::not_null<sem_t*>     _sem;
            gsl::not_null<T*>         _res;
        };

        LockResource()
            :_resource{}
            ,_sem{ std::make_unique<DynamicSemaphore>(1) }
        {}

        LockResource(T&& val)
            :_resource{std::move(val)}
            ,_sem{ std::make_unique<DynamicSemaphore>(1) }
        {}

        LockResource(const LockResource &) = delete;

        LockResource(LockResource &&other)
            :_resource{std::move(other._buffer)}
            ,_sem{std::move(other._sem)}
        {}

        auto operator=(const LockResource  &other) -> LockResource& = delete;

        auto operator=(LockResource  &&other) -> LockResource& {
            _resource = std::move(other._resource);
            _sem = std::move(other._sem);
            return this;
        }

        auto get_accessor() -> LockAccessor
        {
            _sem->acquire();
            return LockAccessor{*_sem, _resource};
        }

        auto get_accessor() const -> const LockAccessor
        {
            _sem->acquire();
            return LockAccessor{*_sem, _resource};
        }

        private:
        T   _resource;
        utils::Uptr<DynamicSemaphore>   _sem;
    }; 

    
    template <typename T, typename ... Args>
    auto create_lock_resource(Args&& ... args) -> LockResource<T>
    {
        return LockResource<T>{ T{ std::forward<Args>(args)... } };
    }
    
} // namespace nitros::media

#endif