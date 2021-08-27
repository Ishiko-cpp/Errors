/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_MESSAGEERROREXTENSION_HPP_
#define _ISHIKO_CPP_ERRORS_MESSAGEERROREXTENSION_HPP_

#include "ErrorExtension.hpp"
#include <string>

namespace Ishiko
{

class MessageErrorExtension : public ErrorExtension
{
public:
    MessageErrorExtension();
    MessageErrorExtension(const std::string& message, const char* file, int line);

    bool tryGetMessage(std::string& message) const noexcept override;
    bool tryGetOrigin(const char*& file, int& line) const noexcept override;

    void onFail(int code, const std::string& message, const char* file, int line) noexcept override;

    std::ostream& operator<<(std::ostream& os) const override;

    const std::string& message() const;
    const std::string& file() const;
    int line() const;

private:
    std::string m_message;
    std::string m_file;
    int m_line;
};

}

#endif
