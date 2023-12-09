

#ifndef _NITROS_UTILS_INTERNAL_LOG_HPP
#define _NITROS_UTILS_INTERNAL_LOG_HPP

#include <spdlog/spdlog.h>
#include "utilities/logger/logger.hpp"

namespace nitros::utils::log
{
    auto Logger() -> std::shared_ptr<spdlog::logger>;
} // namespace nitros::utils::log


#endif