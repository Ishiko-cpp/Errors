/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_ERRORCATEGORY_HPP
#define GUARD_ISHIKO_CPP_ERRORS_ERRORCATEGORY_HPP

#include <string>
#include <system_error>

namespace Ishiko
{

class Error;

class ErrorCategory : public std::error_category
{
public:
    std::string message(int ev) const override;
    virtual const char* message(int ev, char* buffer, size_t len) const noexcept;

protected:
    ErrorCategory() noexcept = default;
    virtual ~ErrorCategory() = default;
};

}

#endif
