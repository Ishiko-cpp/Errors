/*
    Copyright (c) 2017-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "Error.hpp"
#include "Exception.hpp"
#include "InfoErrorExtension.hpp"

using namespace Ishiko;

bool Error::Extensions::tryGetMessage(std::string& message) const noexcept
{
    bool result = false;

    const InfoErrorExtension* extension;
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

bool Error::Extensions::tryGetOrigin(ErrorString& file, int& line) const noexcept
{
    const InfoErrorExtension* extension;
    if (tryGet(extension))
    {
        file = extension->file();
        line = extension->line();
        return true;
    }
    else
    {
        return false;
    }
}

ErrorCondition Error::Extensions::setDynamic(bool dynamic) noexcept
{
    if (!m_impl)
    {
        m_impl.reset(new(std::nothrow) Impl);
        if (!m_impl)
        {
            return ErrorCondition{ErrorsErrorCategory::Get(), ErrorsErrorCategory::Value::memory_allocation_failure};
        }
    }
    m_impl->m_dynamic = dynamic;
    return ErrorCondition{};
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

bool Error::tryGetOrigin(ErrorString& file, int& line) const noexcept
{
    bool result = false;

    if (*this)
    {
        result = m_extensions.tryGetOrigin(file, line);
    }

    return result;
}

void Error::fail(const ErrorCategory& category, int value) noexcept
{
    if (!m_condition)
    {
        m_condition.fail(category, value);
    }
}

void Error::fail(const ErrorCategory& category, int value, const std::string& message, const char* file,
    int line) noexcept
{
    if (!m_condition)
    {
        InfoErrorExtension::Set(*this, message, file, line);
        m_condition.fail(category, value);
    }
}

void Error::fail(const Error& error) noexcept
{
    // TODO: can/should this copy more than the condition and category?
    fail(error.condition().category(), error.condition().value());
}

std::ostream& Ishiko::operator<<(std::ostream& os, const Error& error)
{
    os << error.condition();
    
    const InfoErrorExtension* extension;
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
        ErrorString file;
        int line{-1};
        bool found = error.tryGetOrigin(file, line);
        if (found)
        {
            throw Exception(error.condition(), file.toString().c_str(), line);
        }
        else
        {
            throw Exception(error.condition(), __FILE__, __LINE__);
        }
    }
}
