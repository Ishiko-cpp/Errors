/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorCode.hpp"

using namespace Ishiko;

int ErrorCode::value() const noexcept
{
    return m_value;
}

const ErrorCategory& ErrorCode::category() const noexcept
{
    return *m_category;
}

void ErrorCode::fail(const ErrorCategory& category, int value) noexcept
{
    m_category = &category;
    m_value = value;
}

std::ostream& Ishiko::operator<<(std::ostream& os, const ErrorCode& condition)
{
    os << condition.category().name() << " " << condition.value() << " (";
    os << condition.category().message(condition.value());
    os << ")";
    return os;
}
