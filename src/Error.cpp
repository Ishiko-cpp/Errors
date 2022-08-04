/*
    Copyright (c) 2017-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "Error.hpp"
#include "Exception.hpp"

using namespace Ishiko;

Error::Error(int code, const ErrorCategory& category) noexcept
    : m_condition{code, category}
{
}

Error::operator bool() const noexcept
{
    return (bool)m_condition;
}

bool Error::operator!() const noexcept
{
    return !m_condition;
}

bool Error::operator==(const ErrorCondition& other) const noexcept
{
    return (m_condition == other);
}

bool Error::operator!=(const ErrorCondition& other) const noexcept
{
    return (m_condition != other);
}

bool Error::tryGetMessage(std::string& message) const noexcept
{
    bool result = false;

    if (*this && m_extensions.m_extension)
    {
        result = m_extensions.m_extension->tryGetMessage(message);
    }

    return result;
}

bool Error::tryGetOrigin(const char*& file, int& line) const noexcept
{
    bool result = false;

    if (*this && m_extensions.m_extension)
    {
        result = m_extensions.m_extension->tryGetOrigin(file, line);
    }

    return result;
}

void Error::fail(int code, const ErrorCategory& category) noexcept
{
    if (m_extensions.m_extension)
    {
        m_extensions.m_extension->onFail(code, "", "", -1);
    }
    
    if (!m_condition)
    {
        m_condition.fail(code, category);
    }
}

void Error::fail(int code, const ErrorCategory& category, const std::string& message, const char* file, int line) noexcept
{
    if (m_extensions.m_extension)
    {
        m_extensions.m_extension->onFail(code, message, file, line);
    }

    if (!m_condition)
    {
        m_condition.fail(code, category);
    }
}

void Error::fail(const Error& error) noexcept
{
    // TODO: can/should this copy more than the condition and category?
    fail(error.condition().value(), error.condition().category());
}

void Error::succeed() noexcept
{
    m_condition.succeed();
}

std::ostream& Ishiko::operator<<(std::ostream& os, const Error& error)
{
    os << error.condition();
    
    const ErrorExtension* extension;
    if (error.tryGetExtension(extension))
    {
        extension->operator<<(os);
    }
    return os;
}

void Ishiko::ThrowIf(const Error& error)
{
    if (error)
    {
        const char* file = nullptr;
        int line = -1;
        bool found = error.tryGetOrigin(file, line);
        if (found)
        {
            throw Exception(error.condition(), file, line);
        }
        else
        {
            throw Exception(error.condition(), __FILE__, __LINE__);
        }
    }
}
