/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_ERRORCONDITION_H_
#define _ISHIKO_ERRORS_ERRORCONDITION_H_

#include "ErrorCategory.h"
#include <ostream>

namespace Ishiko
{

class ErrorCondition
{
public:
    ErrorCondition() noexcept;
    explicit ErrorCondition(int value) noexcept;
    ErrorCondition(int value, const ErrorCategory& category) noexcept;

    explicit operator bool() const noexcept;
    bool operator!() const noexcept;

    int value() const noexcept;

    void fail(int value);
    void succeed() noexcept;

private:
    int m_value;
};

std::ostream& operator<<(std::ostream& os, const ErrorCondition& condition);

}

#endif
