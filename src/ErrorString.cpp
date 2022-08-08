/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorMessage.hpp"

using namespace Ishiko;

ErrorMessage& ErrorMessage::assign(const std::string& str) noexcept
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

std::string ErrorMessage::toString() const
{
    return m_data;
}

std::ostream& Ishiko::operator<<(std::ostream& os, const ErrorMessage& error)
{
    return (os << error.m_data);
}
