/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "MessageErrorExtension.h"

namespace Ishiko
{

MessageErrorExtension::MessageErrorExtension()
    : m_line(-1)
{
}

MessageErrorExtension::MessageErrorExtension(const std::string& message, const char* file, int line)
    : m_message(message), m_file(file), m_line(line)
{
}

bool MessageErrorExtension::tryGetMessage(std::string& message) const noexcept
{
    bool result = false;

    if (!m_message.empty())
    {
        message = m_message;
        result = true;
    }

    return result;
}

bool MessageErrorExtension::tryGetOrigin(const char*& file, int& line) const noexcept
{
    bool result = false;

    if ((!m_file.empty()) && (m_line != -1))
    {
        file = m_file.c_str();
        line = m_line;
        result = true;
    }

    return result;
}

void MessageErrorExtension::onFail(int code, const std::string& message, const char* file, int line) noexcept
{
    if (m_message.empty())
    {
        m_message = message;
        m_file = file;
        m_line = line;
    }
}

std::ostream& MessageErrorExtension::operator<<(std::ostream& os) const
{
    if (m_message.size() > 0)
    {
        os << ", " << m_message;
    }
    if (m_file.size() > 0)
    {
        os << " [file: " << m_file << ", line: " << m_line << "]";
    }
    return os;
}

const std::string& MessageErrorExtension::message() const
{
    return m_message;
}

const std::string& MessageErrorExtension::file() const
{
    return m_file;
}

int MessageErrorExtension::line() const
{
    return m_line;
}

}
