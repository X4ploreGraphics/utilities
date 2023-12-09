

#ifndef NITROS_UTILS_DYNAMIC_SEMAPHORE_HPP
#define NITROS_UTILS_DYNAMIC_SEMAPHORE_HPP

#include <mutex>
#include <condition_variable>
#include <atomic>

namespace nitros::utils
{
    class DynamicSemaphore
    {
        public:
        explicit DynamicSemaphore(std::size_t  size) noexcept
            :_size{size}
            ,_count{size}
            ,_mutex{}
            ,_cv{}
        {}
        DynamicSemaphore(const DynamicSemaphore &) = delete;
        DynamicSemaphore(DynamicSemaphore &&) = delete;
        ~DynamicSemaphore() = default;

        auto operator=(const DynamicSemaphore &) -> DynamicSemaphore& = delete;
        auto operator=(DynamicSemaphore &&) -> DynamicSemaphore& = delete;

        void acquire()
        {
            auto lock = std::unique_lock<std::mutex>{_mutex};
            while (_count == 0)
            {
                _cv.wait(lock);
            }
            _count--;
        }

        void release()
        {
            auto lock = std::unique_lock<std::mutex>{_mutex};
            if(_count == _size)
                return;
            _count++;
            _cv.notify_one();
        }

        private:
        std::size_t               _size;
        std::atomic<std::size_t>  _count;
        std::mutex                _mutex;
        std::condition_variable   _cv;
    };    
} // namespace nitros::backend
#endif