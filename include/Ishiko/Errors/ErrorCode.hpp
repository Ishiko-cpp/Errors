/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_ERRORCODE_HPP
#define GUARD_ISHIKO_CPP_ERRORS_ERRORCODE_HPP

#include "ErrorCategory.hpp"
#include "SuccessCategory.hpp"
#include <ostream>
#include <typeinfo>

namespace Ishiko
{

class ErrorCode
{
public:
    ErrorCode() noexcept = default;
    inline ErrorCode(const ErrorCategory& category, int value) noexcept;

    inline explicit operator bool() const noexcept;
    inline bool operator!() const noexcept;
    inline bool operator==(const ErrorCode& other) const noexcept;
    inline bool operator!=(const ErrorCode& other) const noexcept;

    int value() const noexcept;
    const ErrorCategory& category() const noexcept;

    void fail(const ErrorCategory& category, int value) noexcept;
    inline void clear() noexcept;

    inline operator std::error_code() const;

private:
    const ErrorCategory* m_category{&SuccessCategory::Get()};
    int m_value{0};
};

std::ostream& operator<<(std::ostream& os, const ErrorCode& condition);

}

Ishiko::ErrorCode::ErrorCode(const ErrorCategory& category, int value) noexcept
    : m_category(&category), m_value(value)
{
}

Ishiko::ErrorCode::operator bool() const noexcept
{
    return (m_value != 0);
}

bool Ishiko::ErrorCode::operator!() const noexcept
{
    return (m_value == 0);
}

bool Ishiko::ErrorCode::operator==(const ErrorCode& other) const noexcept
{
    return ((m_value == other.m_value) && (typeid(*m_category) == typeid(*other.m_category)));
}

bool Ishiko::ErrorCode::operator!=(const ErrorCode& other) const noexcept
{
    return !(*this == other);
}

void Ishiko::ErrorCode::clear() noexcept
{
    m_value = 0;
    m_category = &SuccessCategory::Get();
}

Ishiko::ErrorCode::operator std::error_code() const
{
    return std::error_code(m_value, *m_category);
}

#endif
