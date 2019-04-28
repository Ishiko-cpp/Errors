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

#ifndef _ISHIKO_ERRORS_ERROR_H_
#define _ISHIKO_ERRORS_ERROR_H_

#include "ErrorExtension.h"
#include <ostream>
#include <string>

namespace Ishiko
{

/// A class to represent errors.

/// An error code of 0 indicates success. Anything else is an error whether it is positive or negative.
class Error
{
public:
    /// Extension types.
    /**
        This enumeration is meant to be used with the Error(Extension e) constructor.
    */
    enum Extension
    {
        /// Extension type associated with the ThrowErrorExtension extension class.
        ThrowException
    };

    /// Creates a new error with an error code set to -1.
    Error();
    /// Creates a new error from the error code passed in as argument.
    explicit Error(int code);
    /// Creates a new error from the error code passed in as argument and sets an extension.
    /**
        @param code The error code.
        @param extension The extension.
    */
    explicit Error(int code, ErrorExtension* extension);
    /// Creates a new error with the given extension.
    /**
        This constructor is used to create an error that throws an exception on failure. It is invoked as follows:

            Error anError(ThrowException); // if fail is called an exception will be thrown

        The exception thrown is of class Exception.

        Behind the scenes this sets the extension to a ThrowErrorExtension singleton.
        
        @param e The extension.
    */
    explicit Error(Extension e);
    /// Destructor.
    /**
        The destructor will call ErrorExtension::release() on the extension.
    */
    ~Error();

    /// Converts the error to a boolean value.
    /**
        @retval true The error code is different than 0.
        @retval false The error code is 0.
    */
    explicit operator bool() const;
    /// Converts the error to a boolean value.
    /**
        @retval true The error code is 0.
        @retval false The error code is different than 0.
    */
    bool operator!() const;
    /// Gets the error code.
    /**
        @returns The error code.
    */
    int code() const;

    /// Sets the error code if the current code is 0.
    /**
        If the current error code is 0 then this function will set it to the value passed in as argument. But the error
        code will remain unchanged if it was different from 0.

        @param code The error code.
    */
    void fail(int code);
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
    void fail(int code, const std::string& message, const char* file, int line);
    /// Sets the error code to 0 regardless of its current value.
    void succeed();

    /// Gets the extension.
    /**
        @returns The extension or 0 if no extension has been set.
    */
    const ErrorExtension* extension() const;
    /// Gets the extension.
    /**
        @returns The extension or 0 if no extension has been set.
    */
    ErrorExtension* extension();

private:
    int m_code;
    ErrorExtension* m_extension;
};

std::ostream& operator<<(std::ostream& os, const Error& error);

}

#include "linkoptions.h"

#endif
