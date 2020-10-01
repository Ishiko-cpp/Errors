/*
    Copyright (c) 2017-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "Error.h"

namespace Ishiko
{

Error::Error() noexcept
    : m_extension(0)
{
}

Error::Error(int code, const ErrorCategory& category) noexcept
    : m_condition(code, category), m_extension(0)
{
}

Error::Error(ErrorExtension* extension) noexcept
    : m_extension(extension)
{
}

Error::Error(int code, const ErrorCategory& category, ErrorExtension* extension) noexcept
    : m_condition(code, category), m_extension(extension)
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
    return (bool)m_condition;
}

bool Error::operator!() const noexcept
{
    return !m_condition;
}

const ErrorCondition& Error::condition() const noexcept
{
    return m_condition;
}

void Error::fail(int code, const ErrorCategory& category)
{
    if (m_extension)
    {
        m_extension->onFail(code, "", "", -1);
    }
    
    if (!m_condition)
    {
        m_condition = ErrorCondition(code, category);
    }
}

void Error::fail(int code, const ErrorCategory& category, const std::string& message, const char* file, int line)
{
    if (m_extension)
    {
        // This will throw an exception if the extension class is ThrowErrorExtension
        m_extension->onFail(code, message, file, line);
    }

    if (!m_condition)
    {
        m_condition = ErrorCondition(code, category);
    }
}

void Error::succeed() noexcept
{
    m_condition.succeed();
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
    os << "Error: "<< error.condition();
    const ErrorExtension* extension = error.extension();
    if (extension)
    {
        extension->operator<<(os);
    }
    return os;
}

}
