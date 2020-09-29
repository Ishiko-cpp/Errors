/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_MESSAGEERROREXTENSION_H_
#define _ISHIKO_ERRORS_MESSAGEERROREXTENSION_H_

#include "ErrorExtension.h"
#include <string>

namespace Ishiko
{

class MessageErrorExtension : public ErrorExtension
{
public:
    MessageErrorExtension();
    MessageErrorExtension(const std::string& message, const char* file, int line);

    void onFail(int code, const std::string& message, const char* file, int line) override;

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
