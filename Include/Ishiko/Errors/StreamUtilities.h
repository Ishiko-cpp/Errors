/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_STREAMUTILITIES_H_
#define _ISHIKO_ERRORS_STREAMUTILITIES_H_

#include "Error.h"
#include <ios>

namespace Ishiko
{

bool FailOnFileCreationError(Error& error, const std::ios& status) noexcept;
bool FailOnFileCreationError(Error& error, const std::ios& status, const std::string& path, const char* file,
    int line) noexcept;

}

#endif
