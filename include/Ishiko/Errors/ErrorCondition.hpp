/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_ERRORCONDITION_HPP
#define GUARD_ISHIKO_CPP_ERRORS_ERRORCONDITION_HPP

#include "ErrorCategory.hpp"
#include "SuccessCategory.hpp"
#include <ostream>

namespace Ishiko
{

class ErrorCondition
{
public:
    ErrorCondition() noexcept = default;
    inline ErrorCondition(int value, const ErrorCategory& category) noexcept;

    explicit operator bool() const noexcept;
    bool operator!() const noexcept;
    bool operator==(const ErrorCondition& other) const noexcept;
    bool operator!=(const ErrorCondition& other) const noexcept;

    int value() const noexcept;
    const ErrorCategory& category() const noexcept;

    void fail(int value, const ErrorCategory& category) noexcept;
    void succeed() noexcept;

private:
    int m_value{0};
    const ErrorCategory* m_category{&SuccessCategory::Get()};
};

std::ostream& operator<<(std::ostream& os, const ErrorCondition& condition);

}

Ishiko::ErrorCondition::ErrorCondition(int value, const ErrorCategory& category) noexcept
    : m_value(value), m_category(&category)
{
}

#endif
