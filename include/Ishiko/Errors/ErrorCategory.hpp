/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_ERRORCATEGORY_HPP
#define GUARD_ISHIKO_CPP_ERRORS_ERRORCATEGORY_HPP

#include <ostream>

namespace Ishiko
{

class Error;

class ErrorCategory
{
public:
    virtual const char* name() const noexcept = 0;

    virtual std::ostream& streamOut(int value, std::ostream& os) const = 0;
    virtual std::ostream& streamOut(const Error& error, std::ostream& os) const;

protected:
    ErrorCategory() noexcept = default;
    virtual ~ErrorCategory() = default;
};

}

#endif
