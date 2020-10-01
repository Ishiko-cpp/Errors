/*
    Copyright (c) 2015-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "Exception.h"

namespace Ishiko
{

Exception::Exception(const std::string& message, const char* file, int line)
#ifdef _WIN32
    : std::exception(message.c_str())
#else
    : std::exception(), m_what(message)
#endif
    , m_file(file), m_line(line)
{
}

Exception::~Exception() throw()
{
}

#ifndef _WIN32
const char* Exception::what() const throw()
{
    return m_what.c_str();
}
#endif

const std::string& Exception::file() const
{
    return m_file;
}

int Exception::line() const
{
    return m_line;
}

}
