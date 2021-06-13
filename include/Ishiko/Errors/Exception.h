/*
    Copyright (c) 2015-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_EXCEPTION_H_
#define _ISHIKO_ERRORS_EXCEPTION_H_

#include "ErrorCondition.h"
#include <stdexcept>

namespace Ishiko
{
	
class Exception : public std::exception
{
public:
    Exception(const ErrorCondition& condition, const char* file, int line);
    Exception(int value, const ErrorCategory& category, const char* file, int line);
    Exception(int value, const ErrorCategory& category, const std::string& description, const char* file, int line);
    
    const char* what() const noexcept override;

    const ErrorCondition& condition() const noexcept;
    const std::string& file() const;
    int line() const;

private:
    ErrorCondition m_condition;
    std::string m_what;
    std::string m_file;
    int m_line;
};

}

#include "linkoptions.h"

#endif
