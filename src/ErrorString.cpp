/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorString.hpp"

using namespace Ishiko;

ErrorString& ErrorString::assign(const std::string& str) noexcept
{
    try
    {
        m_data.assign(str);
    }
    catch (...)
    {
    }
    return *this;
}

std::string ErrorString::toString() const
{
    return m_data;
}

std::ostream& Ishiko::operator<<(std::ostream& os, const ErrorString& error)
{
    return (os << error.m_data);
}
