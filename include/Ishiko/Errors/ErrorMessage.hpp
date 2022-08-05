/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_ERRORMESSAGE_HPP
#define GUARD_ISHIKO_CPP_ERRORS_ERRORMESSAGE_HPP

#include <ostream>
#include <string>

namespace Ishiko
{

class ErrorMessage
{
public:
    inline bool empty() const noexcept;
    inline size_t size() const noexcept;

    ErrorMessage& assign(const std::string& str) noexcept;

    inline bool operator==(const char* other) const noexcept;
    inline bool operator!=(const char* other) const noexcept;

    std::string toString() const;

private:
    friend std::ostream& operator<<(std::ostream& os, const ErrorMessage& error);

    std::string m_data;
};

std::ostream& operator<<(std::ostream& os, const ErrorMessage& error);

}

bool Ishiko::ErrorMessage::empty() const noexcept
{
    return m_data.empty();
}

size_t Ishiko::ErrorMessage::size() const noexcept
{
    return m_data.size();
}

bool Ishiko::ErrorMessage::operator==(const char* other) const noexcept
{
    return (m_data == other);
}

bool Ishiko::ErrorMessage::operator!=(const char* other) const noexcept
{
    return !(*this == other);
}

#endif
