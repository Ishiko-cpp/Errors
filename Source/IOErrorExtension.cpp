/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "IOErrorExtension.h"
#include <errno.h>

namespace Ishiko
{

void IOErrorExtension::Fail(Error& error, EIOErrorCode code, const char* file, int line)
{
    error.fail(EIO, "", file, line);

    IOErrorExtension* ext = dynamic_cast<IOErrorExtension*>(error.extension());
    if (ext)
    {
        ext->m_code = code;
        ext->m_file = file;
        ext->m_line = line;
    }
}

void IOErrorExtension::Fail(Error& error, std::ios& status, const char* file, int line)
{
    if (!status.good())
    {
        error.fail(EIO, "", file, line);

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
