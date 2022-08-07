/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_MESSAGEERROREXTENSION_HPP
#define GUARD_ISHIKO_CPP_ERRORS_MESSAGEERROREXTENSION_HPP

#include "Error.hpp"
#include "ErrorMessage.hpp"
#include <string>

namespace Ishiko
{

class MessageErrorExtension : public Error::Extension
{
public:
    MessageErrorExtension();
    MessageErrorExtension(const std::string& message, const char* file, int line);

    static void Set(Error& error, const std::string& message, const char* file, int line) noexcept;

    bool tryGetOrigin(const char*& file, int& line) const noexcept;

    std::ostream& streamOut(std::ostream& os) const override;

    const ErrorMessage& message() const noexcept;
    const std::string& file() const;
    int line() const;

private:
    ErrorMessage m_message;
    std::string m_file;
    int m_line;
};

}

#endif
