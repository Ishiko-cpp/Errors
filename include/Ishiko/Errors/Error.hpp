/*
    Copyright (c) 2017-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_ERROR_HPP
#define GUARD_ISHIKO_CPP_ERRORS_ERROR_HPP

#include "ErrorCondition.hpp"
#include "ErrorsErrorCategory.hpp"
#include "ErrorString.hpp"
#include <Ishiko/BasePlatform.h>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <typeindex>

namespace Ishiko
{

/// A class to represent errors.

/// An error code of 0 indicates success. Anything else is an error whether it is positive or negative.
class Error
{
public:
    /// Base class for the error extensions.
    class Extension
    {
    public:
        virtual ~Extension() = default;
    };

    class Extensions
    {
    public:
        inline Extensions() noexcept;

        template<typename E> ErrorCondition install() noexcept;

        template<typename E> bool tryGet(const E*& extension) const noexcept;
        template<typename E> bool tryGet(E*& extension) noexcept;

        // TODO: make this noexcept
        bool tryGetMessage(std::string& message) const noexcept;
        // TODO: make this noexcept
        bool tryGetOrigin(ErrorString& file, int& line) const noexcept;

        inline bool dynamic() const noexcept;
        ErrorCondition setDynamic(bool dynamic) noexcept;

    private:
        class Impl
        {
        public:
            bool m_dynamic{false};
            // TODO: need to make this fail silently
            std::map<std::type_index, std::unique_ptr<Extension>> m_extensions;
        };

        std::unique_ptr<Impl> m_impl;
    };

    /// Creates a new error with an error code set to 0.
    Error() noexcept = default;

    /// Creates a new error from the error code passed in as argument.
    inline Error(const ErrorCategory& category, int value) noexcept;

    Error(const Error& other) = delete;
    Error(Error&& other) = delete;

    inline const Extensions& extensions() const noexcept;
    inline Extensions& extensions() noexcept;

    Error& operator=(const Error& other) = delete;
    Error& operator=(Error&& other) = delete;

    /// Converts the error to a boolean value.
    /**
        @retval true The error code is different than 0.
        @retval false The error code is 0.
    */
    explicit operator bool() const noexcept;

    /// Converts the error to a boolean value.
    /**
        @retval true The error code is 0.
        @retval false The error code is different than 0.
    */
    bool operator!() const noexcept;

    bool operator==(const ErrorCondition& other) const noexcept;
    bool operator!=(const ErrorCondition& other) const noexcept;

    /// Gets the error condition.
    /**
        @returns The error condition.
    */
    inline ErrorCondition condition() const noexcept;

    bool tryGetMessage(std::string& message) const noexcept;

    bool tryGetOrigin(ErrorString& file, int& line) const noexcept;

    /// Sets the error code if the current code is 0.
    /**
        If the current error code is 0 then this function will set it to the value passed in as argument. But the error
        code will remain unchanged if it was different from 0.

        @param code The error code.
    */
    void fail(const ErrorCategory& category, int value) noexcept;

    /// Sets the error code if the current code is 0.
    /**
        If the current error code is 0 then this function will set it to the value passed in as argument. But the error
        code will remain unchanged if it was different from 0.

        This function also provides extra information about the error. That extra information can be used by the
        extension.

        @param value The error code.
        @param message A description of the error.
        @param file The file where the fail() function was called.
        @param line The line at which the fail() function was called.
    */
    void fail(const ErrorCategory& category, int value, const std::string& message, const char* file, int line) noexcept;

    void fail(const Error& error) noexcept;

    /// Sets the error code to 0 regardless of its current value.
    inline void clear() noexcept;

private:
    ErrorCondition m_condition;
    Extensions m_extensions;
};

std::ostream& operator<<(std::ostream& os, const Error& error);

void ThrowIf(const Error& error);

}

Ishiko::Error::Extensions::Extensions() noexcept
{
#ifdef ISHIKO_DEBUG
    setDynamic(true);
#endif
}

template<typename E>
Ishiko::ErrorCondition Ishiko::Error::Extensions::install() noexcept
{
    if (!m_impl)
    {
        m_impl.reset(new(std::nothrow) Impl);
        if (!m_impl)
        {
            return ErrorCondition{ErrorsErrorCategory::Get(), ErrorsErrorCategory::Value::memory_allocation_error};
        }
    }
    m_impl->m_extensions[typeid(E)].reset(new(std::nothrow) E());
    return ErrorCondition{};
}

template<typename E>
bool Ishiko::Error::Extensions::tryGet(const E*& extension) const noexcept
{
    if (m_impl)
    {
        const E* result = dynamic_cast<const E*>(m_impl->m_extensions[typeid(E)].get());
        if (result)
        {
            extension = result;
            return true;
        }
    }
    return false;
}

template<typename E>
bool Ishiko::Error::Extensions::tryGet(E*& extension) noexcept
{
    if (m_impl)
    {
        E* result = dynamic_cast<E*>(m_impl->m_extensions[typeid(E)].get());
        if (result)
        {
            extension = result;
            return true;
        }
    }
    return false;
}

bool Ishiko::Error::Extensions::dynamic() const noexcept
{
    return (m_impl ? m_impl->m_dynamic : false);
}

Ishiko::Error::Error(const ErrorCategory& category, int value) noexcept
    : m_condition{category, value}
{
}

const Ishiko::Error::Extensions& Ishiko::Error::extensions() const noexcept
{
    return m_extensions;
}

Ishiko::Error::Extensions& Ishiko::Error::extensions() noexcept
{
    return m_extensions;
}

Ishiko::ErrorCondition Ishiko::Error::condition() const noexcept
{
    return m_condition;
}

void Ishiko::Error::clear() noexcept
{
    m_condition.clear();
}

#endif
