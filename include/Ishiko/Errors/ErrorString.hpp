/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_ERRORSTRING_HPP
#define GUARD_ISHIKO_CPP_ERRORS_ERRORSTRING_HPP

#include <ostream>
#include <string>

namespace Ishiko
{

// TODO: a string class that doesn't throw exceptions, fails silently. This is because we are creating an error message
// and if that fails we don't want to report that as an error instead of the original error. The case where we'd
// actually run out of memory should be very rare anyway.
class ErrorString
{
public:
    inline bool empty() const noexcept;
    inline size_t size() const noexcept;

    ErrorString& assign(const std::string& str) noexcept;

    inline bool operator==(const char* other) const noexcept;
    inline bool operator!=(const char* other) const noexcept;

    std::string toString() const;

private:
    friend std::ostream& operator<<(std::ostream& os, const ErrorString& error);

    std::string m_data;
};

std::ostream& operator<<(std::ostream& os, const ErrorString& error);

}

bool Ishiko::ErrorString::empty() const noexcept
{
    return m_data.empty();
}

size_t Ishiko::ErrorString::size() const noexcept
{
    return m_data.size();
}

bool Ishiko::ErrorString::operator==(const char* other) const noexcept
{
    return (m_data == other);
}

bool Ishiko::ErrorString::operator!=(const char* other) const noexcept
{
    return !(*this == other);
}

#endif
