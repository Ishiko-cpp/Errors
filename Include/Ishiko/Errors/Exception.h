/*
    Copyright (c) 2015-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_EXCEPTION_H_
#define _ISHIKO_ERRORS_EXCEPTION_H_

#include <stdexcept>

namespace Ishiko
{
	
class Exception : public std::exception
{
public:
    Exception(const std::string& message, const char* file, int line);
    virtual ~Exception() throw();

#ifndef _WIN32
    virtual const char* what() const throw();
#endif

    const std::string& file() const;
    int line() const;

private:
#ifndef _WIN32
    // The Visual C++ STL has custom support for the what information
    // so we use it. On other platforms we define our own variable to
    // store that information.
    std::string m_what;
#endif
    std::string m_file;
    int m_line;
};

}

#include "linkoptions.h"

#endif
