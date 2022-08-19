/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_INFOERROREXTENSION_HPP
#define GUARD_ISHIKO_CPP_ERRORS_INFOERROREXTENSION_HPP

#include "Error.hpp"
#include "ErrorString.hpp"
#include <string>

namespace Ishiko
{

class InfoErrorExtension : public Error::Extension
{
public:
    InfoErrorExtension();
    InfoErrorExtension(const std::string& message, const char* file, int line);
    InfoErrorExtension(const std::wstring& message, const char* file, int line);

    static void Set(Error& error, const std::string& message, const char* file, int line) noexcept;
    static void Set(Error& error, const std::wstring& message, const char* file, int line) noexcept;

    std::ostream& streamOut(std::ostream& os) const;

    const ErrorString& message() const noexcept;
    const ErrorString& file() const;
    int line() const;

private:
    ErrorString m_message;
    ErrorString m_file;
    int m_line;
};

}

#endif
