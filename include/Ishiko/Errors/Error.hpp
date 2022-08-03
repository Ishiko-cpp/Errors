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
    /// Creates a new error with an error code set to 0.
    Error() noexcept = default;

    /// Creates a new error from the error code passed in as argument.
    Error(int code, const ErrorCategory& category) noexcept;

    explicit Error(ErrorExtension* extension) noexcept;

    /// Creates a new error from the error code passed in as argument and sets an extension.
    /**
        @param code The error code.
        @param extension The extension.
    */
    Error(int code, const ErrorCategory& category, ErrorExtension* extension) noexcept;

    Error(const Error& other) = delete;
    Error(Error&& other) = delete;

    /// Destructor.
    /**
        The destructor will call ErrorExtension::release() on the extension.
    */
    ~Error() noexcept;

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
    const ErrorCondition& condition() const noexcept;

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

    /// Gets the extension.
    /**
        @returns The extension or 0 if no extension has been set.
    */
    const ErrorExtension* extension() const noexcept;

    /// Gets the extension.
    /**
        @returns The extension or 0 if no extension has been set.
    */
    ErrorExtension* extension() noexcept;

private:
    ErrorCondition m_condition;
    ErrorExtension* m_extension{nullptr};
};

std::ostream& operator<<(std::ostream& os, const Error& error);

void ThrowIf(const Error& error);

}

#endif
