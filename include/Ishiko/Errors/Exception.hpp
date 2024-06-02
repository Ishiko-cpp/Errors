/*
    Copyright (c) 2015-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_EXCEPTION_HPP
#define GUARD_ISHIKO_CPP_ERRORS_EXCEPTION_HPP

#include "ErrorCode.hpp"
#include <stdexcept>

namespace Ishiko
{
	
class Exception : public std::exception
{
public:
    Exception(const ErrorCode& code, const char* file, int line);
    Exception(int value, const ErrorCategory& category, const char* file, int line);
    Exception(int value, const ErrorCategory& category, const std::string& description, const char* file, int line);
    
    const char* what() const noexcept override;

    const ErrorCode& code() const noexcept;
    const std::string& file() const;
    int line() const;

private:
    ErrorCode m_code;
    std::string m_what;
    std::string m_file;
    int m_line;
};

}

#endif
