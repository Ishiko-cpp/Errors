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
    enum Extension
    {
        ThrowException
    };

    /// This constructor creates a new error with an error code set to -1.
    Error();
    /// This constructor creates a new error from the error code passed in as argument.
    explicit Error(int code);
    explicit Error(int code, ErrorExtension* extension);
    explicit Error(Extension e);
    ~Error();

    explicit operator bool() const;
    bool operator!() const;
    int code() const;

    /// If the current error code is 0 then this function will set it to the value passed in as argument. But the error
    /// code will remain unchanged if it was different from 0.
    void fail(int code);
    void fail(int code, const std::string& message, const char* file, int line);
    /// Sets the error code to 0 regardless of its current value.
    void succeed();

private:
    int m_code;
    ErrorExtension* m_extension;
};

std::ostream& operator<<(std::ostream& os, const Error& error);

}

#include "linkoptions.h"

#endif
