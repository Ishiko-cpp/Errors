/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "ErrorCondition.h"
#include "SuccessCategory.h"

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

int ErrorCondition::value() const noexcept
{
    return m_value;
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
    // TODO: add category
    os << condition.value();
    return os;
}

}
