/*
    Copyright (c) 2015-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "Exception.h"

namespace Ishiko
{

Exception::Exception(const ErrorCondition& condition, const char* file, int line)
    : m_condition(condition), m_file(file), m_line(line)
{
}

Exception::Exception(int value, const ErrorCategory& category, const char* file, int line)
    : m_condition(value, category), m_file(file), m_line(line)
{
}

Exception::Exception(int value, const ErrorCategory& category, const std::string& description, const char* file,
    int line)
    : m_condition(value, category), m_what(description), m_file(file), m_line(line)
{
}

const char* Exception::what() const noexcept
{
    return m_what.c_str();
}

const ErrorCondition& Exception::condition() const noexcept
{
    return m_condition;
}

const std::string& Exception::file() const
{
    return m_file;
}

int Exception::line() const
{
    return m_line;
}

}
