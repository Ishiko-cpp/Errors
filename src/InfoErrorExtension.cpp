/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "InfoErrorExtension.hpp"

using namespace Ishiko;

InfoErrorExtension::InfoErrorExtension()
    : m_line(-1)
{
}

InfoErrorExtension::InfoErrorExtension(const std::string& message, const char* file, int line)
    : m_file(file), m_line(line)
{
    m_message.assign(message);
}

void InfoErrorExtension::Set(Error& error, const std::string& message, const char* file, int line) noexcept
{
    InfoErrorExtension* extension;
    if (error.extensions().tryGet(extension))
    {
        extension->m_message.assign(message);
        extension->m_file = file;
        extension->m_line = line;
    }
}

bool InfoErrorExtension::tryGetOrigin(const char*& file, int& line) const noexcept
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

std::ostream& InfoErrorExtension::streamOut(std::ostream& os) const
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

const ErrorString& InfoErrorExtension::message() const noexcept
{
    return m_message;
}

const std::string& InfoErrorExtension::file() const
{
    return m_file;
}

int InfoErrorExtension::line() const
{
    return m_line;
}
