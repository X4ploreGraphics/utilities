

#ifndef NITROS_UTILS_FUTURE_HPP
#define NITROS_UTILS_FUTURE_HPP

#include <future>
#include <chrono>

namespace nitros::utils
{
    template <typename T>
    inline auto is_ready(const std::future<T>& job) -> bool {
    	return std::future_status::ready == job.wait_for(std::chrono::microseconds(0));
    }    
} // namespace nitros::utils

#endif