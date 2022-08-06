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
    inline ErrorCondition(const ErrorCategory& category, int value) noexcept;

    explicit operator bool() const noexcept;
    bool operator!() const noexcept;
    bool operator==(const ErrorCondition& other) const noexcept;
    bool operator!=(const ErrorCondition& other) const noexcept;

    int value() const noexcept;
    const ErrorCategory& category() const noexcept;

    void fail(int value, const ErrorCategory& category) noexcept;
    void succeed() noexcept;

private:
    const ErrorCategory* m_category{&SuccessCategory::Get()};
    int m_value{0};
};

std::ostream& operator<<(std::ostream& os, const ErrorCondition& condition);

}

Ishiko::ErrorCondition::ErrorCondition(const ErrorCategory& category, int value) noexcept
    : m_category(&category), m_value(value)
{
}

#endif
