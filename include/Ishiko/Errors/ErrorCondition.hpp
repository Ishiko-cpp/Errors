/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_ERRORCONDITION_HPP_
#define _ISHIKO_CPP_ERRORS_ERRORCONDITION_HPP_

#include "ErrorCategory.hpp"
#include <ostream>

namespace Ishiko
{

class ErrorCondition
{
public:
    ErrorCondition() noexcept;
    ErrorCondition(int value, const ErrorCategory& category) noexcept;

    explicit operator bool() const noexcept;
    bool operator!() const noexcept;
    bool operator==(const ErrorCondition& other) const noexcept;
    bool operator!=(const ErrorCondition& other) const noexcept;

    int value() const noexcept;
    const ErrorCategory& category() const noexcept;

    void fail(int value, const ErrorCategory& category) noexcept;
    void succeed() noexcept;

private:
    int m_value;
    const ErrorCategory* m_category;
};

std::ostream& operator<<(std::ostream& os, const ErrorCondition& condition);

}

#endif
