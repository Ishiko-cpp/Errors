/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_ERRORCATEGORY_HPP_
#define _ISHIKO_CPP_ERRORS_ERRORCATEGORY_HPP_

namespace Ishiko
{

class ErrorCategory
{
public:
    virtual const char* name() const noexcept = 0;

protected:
    ErrorCategory() noexcept = default;
    virtual ~ErrorCategory() = default;
};

}

#endif
