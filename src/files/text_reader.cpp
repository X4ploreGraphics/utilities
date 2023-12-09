

#include "utilities/files/files.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <spdlog/spdlog.h>

namespace nitros::utils
{
    std::string TextReader::read(const std::string &file_path)
    {
        std::ifstream file_io;
        std::string data;

        file_io.exceptions(std::ifstream::badbit);

        try
        {

            file_io.open(file_path.c_str());

            std::stringstream str_stream;
            str_stream << file_io.rdbuf();

            file_io.close();

            data = str_stream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::runtime_error("Error Reading File " + file_path);
        }

        return data;
    }

    namespace reader
    {
        std::vector<std::uint8_t> read_binary(const std::string &file_path)
        {
            std::vector<std::uint8_t> data;

            auto file_io = std::ifstream{file_path.c_str(), std::ios_base::binary};
            file_io.exceptions(std::ios_base::badbit | std::ios_base::failbit);
            file_io.seekg(0, file_io.end);
            auto length = file_io.tellg();
            file_io.seekg(0, file_io.beg);
            data.resize(length);

            file_io.read(reinterpret_cast<char *>(data.data()), length);

            return data;
        }

        auto read_binary_as_string(std::string_view  file_path) -> std::string
        {
            auto data = std::string{};

            auto file_io = std::ifstream{file_path.data(), std::ios_base::binary};
            file_io.exceptions(std::ios_base::badbit | std::ios_base::failbit);
            file_io.seekg(0, file_io.end);
            auto length = file_io.tellg();
            file_io.seekg(0, file_io.beg);
            data.resize(length);

            file_io.read(data.data(), length);

            return data;
        }

#if defined(__ANDROID__)
        namespace android
        {
            std::vector<std::uint8_t> read_asset_binary(const std::string &file_path, nitros::utils::android::Asset::mode mode)
            {
                if (auto asset = nitros::utils::android::AssetManager::get_instance().get_asset(file_path, mode))
                {
                    return asset->read();
                }
                return {};
            }
        }
#endif
    } // namespace reader

    namespace writer
    {
        void write_binary(const fs::path  &file_path, std::span<const std::uint8_t>  buffer)
        {
            auto ofstream = std::ofstream{ file_path.c_str(), std::ios_base::binary | std::ios_base::out };
            ofstream.write( reinterpret_cast<const char*>(buffer.data()), buffer.size() );

            ofstream.flush();
            ofstream.close();
        }
    }
}