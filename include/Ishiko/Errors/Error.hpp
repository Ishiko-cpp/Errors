/*
    Copyright (c) 2017-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_ERROR_HPP
#define GUARD_ISHIKO_CPP_ERRORS_ERROR_HPP

#include "ErrorCondition.hpp"
#include "ErrorExtension.hpp"
#include <ostream>
#include <string>

namespace Ishiko
{

/// A class to represent errors.

/// An error code of 0 indicates success. Anything else is an error whether it is positive or negative.
class Error
{
public:
    class Extensions
    {
    public:
        inline ~Extensions();

        template<typename Extension> bool install() noexcept;

        ErrorExtension* m_extension{nullptr};
    };

    /// Creates a new error with an error code set to 0.
    Error() noexcept = default;

    /// Creates a new error from the error code passed in as argument.
    Error(int code, const ErrorCategory& category) noexcept;

    Error(const Error& other) = delete;
    Error(Error&& other) = delete;

    inline const Extensions& extensions() const noexcept;
    inline Extensions& extensions() noexcept;

    template<typename Extension>
    bool tryGetExtension(const Extension*& extension) const noexcept;

    template<typename Extension>
    bool tryGetExtension(Extension*& extension) noexcept;

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

    bool tryGetOrigin(const char*& file, int& line) const noexcept;

    /// Sets the error code if the current code is 0.
    /**
        If the current error code is 0 then this function will set it to the value passed in as argument. But the error
        code will remain unchanged if it was different from 0.

        @param code The error code.
    */
    void fail(int code, const ErrorCategory& category) noexcept;

    /// Sets the error code if the current code is 0.
    /**
        If the current error code is 0 then this function will set it to the value passed in as argument. But the error
        code will remain unchanged if it was different from 0.

        This function also provides extra information about the error. That extra information can be used by the
        extension.

        @param code The error code.
        @param message A description of the error.
        @param file The file where the fail() function was called.
        @param line The line at which the fail() function was called.
    */
    void fail(int code, const ErrorCategory& category, const std::string& message, const char* file, int line) noexcept;

    void fail(const Error& error) noexcept;

    /// Sets the error code to 0 regardless of its current value.
    void succeed() noexcept;

private:
    ErrorCondition m_condition;
    Extensions m_extensions;
};

std::ostream& operator<<(std::ostream& os, const Error& error);

void ThrowIf(const Error& error);

}

template<typename Extension>
bool Ishiko::Error::Extensions::install() noexcept
{
    if (m_extension)
    {
        m_extension->release();
    }
    m_extension = new(std::nothrow) Extension();
    return m_extension;
}

const Ishiko::Error::Extensions& Ishiko::Error::extensions() const noexcept
{
    return m_extensions;
}

Ishiko::Error::Extensions& Ishiko::Error::extensions() noexcept
{
    return m_extensions;
}

template<typename Extension>
bool Ishiko::Error::tryGetExtension(const Extension*& extension) const noexcept
{
    const Extension* result = dynamic_cast<const Extension*>(m_extensions.m_extension);
    if (result)
    {
        extension = result;
        return true;
    }
    else
    {
        return false;
    }
}

template<typename Extension>
bool Ishiko::Error::tryGetExtension(Extension*& extension) noexcept
{
    Extension* result = dynamic_cast<Extension*>(m_extensions.m_extension);
    if (result)
    {
        extension = result;
        return true;
    }
    else
    {
        return false;
    }
}

Ishiko::ErrorCondition Ishiko::Error::condition() const noexcept
{
    return m_condition;
}

Ishiko::Error::Extensions::~Extensions()
{
    if (m_extension)
    {
        m_extension->release();
    }
}

#endif
