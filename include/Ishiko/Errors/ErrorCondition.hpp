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
#include <typeinfo>

namespace Ishiko
{

class ErrorCondition
{
public:
    ErrorCondition() noexcept = default;
    inline ErrorCondition(const ErrorCategory& category, int value) noexcept;

    inline explicit operator bool() const noexcept;
    inline bool operator!() const noexcept;
    inline bool operator==(const ErrorCondition& other) const noexcept;
    inline bool operator!=(const ErrorCondition& other) const noexcept;

    int value() const noexcept;
    const ErrorCategory& category() const noexcept;

    void fail(int value, const ErrorCategory& category) noexcept;
    inline void clear() noexcept;

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

Ishiko::ErrorCondition::operator bool() const noexcept
{
    return (m_value != 0);
}

bool Ishiko::ErrorCondition::operator!() const noexcept
{
    return (m_value == 0);
}

bool Ishiko::ErrorCondition::operator==(const ErrorCondition& other) const noexcept
{
    return ((m_value == other.m_value) && (typeid(*m_category) == typeid(*other.m_category)));
}

bool Ishiko::ErrorCondition::operator!=(const ErrorCondition& other) const noexcept
{
    return !(*this == other);
}

void Ishiko::ErrorCondition::clear() noexcept
{
    m_value = 0;
    m_category = &SuccessCategory::Get();
}

#endif
