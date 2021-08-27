/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "IOErrorExtension.hpp"
#include "IOErrorCategory.hpp"
#include <errno.h>

namespace Ishiko
{

void IOErrorExtension::Fail(Error& error, EIOErrorCode code, const char* file, int line)
{
    error.fail(EIO, IOErrorCategory::Get(), "", file, line);

    IOErrorExtension* ext = dynamic_cast<IOErrorExtension*>(error.extension());
    if (ext)
    {
        ext->m_code = code;
        ext->m_file = file;
        ext->m_line = line;
    }
}

void IOErrorExtension::Fail(Error& error, const std::ios& status, const char* file, int line)
{
    if (!status.good())
    {
        error.fail(EIO, IOErrorCategory::Get(), "", file, line);

        EIOErrorCode code = eError;
        if (status.eof())
        {
            code = eEOF;
        }

        IOErrorExtension* ext = dynamic_cast<IOErrorExtension*>(error.extension());
        if (ext)
        {
            ext->m_code = code;
            ext->m_file = file;
            ext->m_line = line;
        }
    }
}

std::ostream& IOErrorExtension::operator<<(std::ostream& os) const
{
    os << ", I/O error: ";
    switch (m_code)
    {
    case eEOF:
        os << "end-of-file";
        break;
    }
    if (m_file.size() > 0)
    {
        os << " [file: " << m_file << ", line: " << m_line << "]";
    }
    return os;
}

IOErrorExtension::EIOErrorCode IOErrorExtension::code() const
{
    return m_code;
}

}
