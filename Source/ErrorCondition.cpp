/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "ErrorCondition.h"

namespace Ishiko
{

ErrorCondition::ErrorCondition() noexcept
    : m_value(-1)
{
}

ErrorCondition::ErrorCondition(int value) noexcept
    : m_value(value)
{
}

ErrorCondition::ErrorCondition(int value, const ErrorCategory& category) noexcept
    : m_value(value)
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

void ErrorCondition::succeed() noexcept
{
    m_value = 0;
}

std::ostream& operator<<(std::ostream& os, const ErrorCondition& condition)
{
    os << condition.value();
    return os;
}

}
