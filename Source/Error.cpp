/*
    Copyright (c) 2017-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OROTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "Error.h"

namespace Ishiko
{

Error::Error() noexcept
    : m_code(-1), m_extension(0)
{
}

Error::Error(int code) noexcept
    : m_code(code), m_extension(0)
{
}

Error::Error(int code, ErrorExtension* extension) noexcept
    : m_code(code), m_extension(extension)
{
}

Error::~Error() noexcept
{
    if (m_extension)
    {
        m_extension->release();
    }
}

Error::operator bool() const noexcept
{
    return (m_code != 0);
}

bool Error::operator!() const noexcept
{
    return (m_code == 0);
}

int Error::code() const noexcept
{
    return m_code;
}

void Error::fail(int code)
{
    if (m_extension)
    {
        m_extension->onFail(code, "", "", -1);
    }
    
    if (m_code == 0)
    {
        m_code = code;
    }
}

void Error::fail(int code, const std::string& message, const char* file, int line)
{
    if (m_extension)
    {
        // This will throw an exception if the extension class is ThrowErrorExtension
        m_extension->onFail(code, message, file, line);
    }

    if (m_code == 0)
    {
        m_code = code;
    }
}

void Error::succeed() noexcept
{
    m_code = 0;
}

const ErrorExtension* Error::extension() const noexcept
{
    return m_extension;
}

ErrorExtension* Error::extension() noexcept
{
    return m_extension;
}

std::ostream& operator<<(std::ostream& os, const Error& error)
{
    os << "Error: "<< error.code();
    const ErrorExtension* extension = error.extension();
    if (extension)
    {
        extension->operator<<(os);
    }
    return os;
}

}
