

#ifndef NITROS_UTILS_LOGGER_HPP
#define NITROS_UTILS_LOGGER_HPP

#include "utilities/utils_export.h"
#include <string>
#include <spdlog/spdlog.h>

namespace nitros::utils
{
	NUTILS_EXPORT std::shared_ptr<spdlog::logger>	setup_logger(spdlog::sinks_init_list sinks);	
}

#endif