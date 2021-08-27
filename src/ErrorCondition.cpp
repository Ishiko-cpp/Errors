/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorCondition.hpp"
#include "SuccessCategory.hpp"

namespace Ishiko
{

ErrorCondition::ErrorCondition() noexcept
    : m_value(0), m_category(&SuccessCategory::Get())
{
}

ErrorCondition::ErrorCondition(int value, const ErrorCategory& category) noexcept
    : m_value(value), m_category(&category)
{
}

ErrorCondition::operator bool() const noexcept
{
    return (m_value != 0);
}

bool ErrorCondition::operator!() const noexcept
{
    return (m_value == 0);
}

bool ErrorCondition::operator==(const ErrorCondition& other) const noexcept
{
    return ((m_value == other.m_value) && (m_category == other.m_category));
}

bool ErrorCondition::operator!=(const ErrorCondition& other) const noexcept
{
    return ((m_value != other.m_value) || (m_category != other.m_category));
}

int ErrorCondition::value() const noexcept
{
    return m_value;
}

const ErrorCategory& ErrorCondition::category() const noexcept
{
    return *m_category;
}

void ErrorCondition::fail(int value, const ErrorCategory& category) noexcept
{
    m_value = value;
    m_category = &category;
}

void ErrorCondition::succeed() noexcept
{
    m_value = 0;
    m_category = &SuccessCategory::Get();
}

std::ostream& operator<<(std::ostream& os, const ErrorCondition& condition)
{
    os << condition.category().name() << ", " << condition.value();
    return os;
}

}
