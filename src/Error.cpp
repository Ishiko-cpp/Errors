/*
    Copyright (c) 2017-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "Error.hpp"
#include "MessageErrorExtension.hpp"
#include "Exception.hpp"

using namespace Ishiko;

/*
std::ostream& Error::Extension::streamOut(std::ostream& os) const
{
    // Do nothing
    return os;
}
*/

bool Error::Extensions::tryGetMessage(std::string& message) const noexcept
{
    bool result = false;

    const MessageErrorExtension* extension;
    if (tryGet(extension))
    {
        if (!extension->message().empty())
        {
            message = extension->message().toString();
            result = true;
        }
    }

    return result;
}

bool Error::Extensions::tryGetOrigin(const char*& file, int& line) const noexcept
{
    bool result = false;

    const MessageErrorExtension* extension;
    if (tryGet(extension))
    {
        result = extension->tryGetOrigin(file, line);
    }

    return result;
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

    if (*this)
    {
        result = m_extensions.tryGetMessage(message);
    }

    return result;
}

bool Error::tryGetOrigin(const char*& file, int& line) const noexcept
{
    bool result = false;

    if (*this)
    {
        result = m_extensions.tryGetOrigin(file, line);
    }

    return result;
}

void Error::fail(int code, const ErrorCategory& category) noexcept
{
    if (!m_condition)
    {
        m_condition.fail(code, category);
    }
}

void Error::fail(int code, const ErrorCategory& category, const std::string& message, const char* file, int line) noexcept
{
    if (!m_condition)
    {
        MessageErrorExtension::Set(*this, message, file, line);
        m_condition.fail(code, category);
    }
}

void Error::fail(const Error& error) noexcept
{
    // TODO: can/should this copy more than the condition and category?
    fail(error.condition().value(), error.condition().category());
}

std::ostream& Ishiko::operator<<(std::ostream& os, const Error& error)
{
    os << error.condition();
    
    const MessageErrorExtension* extension;
    if (error.extensions().tryGet(extension))
    {
        extension->streamOut(os);
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
