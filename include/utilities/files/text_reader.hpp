

#ifndef TEXTREADER_HPP
#define TEXTREADER_HPP

#include <string>
#include <utilities/utils_export.h>

namespace nitros::utils
{

class TextReader
{
public:
    static NUTILS_EXPORT std::string read(const std::string &file_path);
};

}


#endif // TEXTREADER_HPP
