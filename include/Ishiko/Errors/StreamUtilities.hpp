/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_STREAMUTILITIES_HPP_
#define _ISHIKO_CPP_ERRORS_STREAMUTILITIES_HPP_

#include "Error.hpp"
#include <ios>

namespace Ishiko
{

bool FailIfCreateFileError(Error& error, const std::ios& status) noexcept;
bool FailIfCreateFileError(Error& error, const std::ios& status, const std::string& path, const char* file,
    int line) noexcept;
bool FailIfOpenFileError(Error& error, const std::ios& status) noexcept;
bool FailIfOpenFileError(Error& error, const std::ios& status, const std::string& path, const char* file,
    int line) noexcept;

}

#endif
