

#ifndef NITROS_UTILITIES_READER_HPP
#define NITROS_UTILITIES_READER_HPP

#include "text_reader.hpp"
#include "utilities/utils_export.h"
#include "utilities/filesystem.hpp"
#if defined(__ANDROID__)
#include "utilities/platform/Android/asset_manager.hpp"
#endif
#include <vector>
#include <span>

namespace nitros::utils
{
    namespace reader
    {
        //Throws exception std::ifstream::failure if the reading failes
        NUTILS_EXPORT std::vector<std::uint8_t>   read_binary(const std::string &file_path);

        //Throws exception std::ifstream::failure if the reading failes
        NUTILS_EXPORT auto read_binary_as_string(std::string_view  file_path) -> std::string;

    #if defined(__ANDROID__)
        namespace android{
            //Returns empty vector if no file can be read
           std::vector<std::uint8_t>   read_asset_binary(const std::string &file_path, nitros::utils::android::Asset::mode  mode);
        }
    #endif
    } // namespace reader

    namespace writer
    {
        NUTILS_EXPORT void write_binary(const fs::path  &file_path, std::span<const std::uint8_t>  buffer);
    }
} // namespace nitros::utils

#endif