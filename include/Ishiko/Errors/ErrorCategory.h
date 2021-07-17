/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_ERRORCATEGORY_H_
#define _ISHIKO_ERRORS_ERRORCATEGORY_H_

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
