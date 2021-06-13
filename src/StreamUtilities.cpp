/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "StreamUtilities.h"
#include "IOErrorCategory.h"

namespace Ishiko
{

bool FailIfCreateFileError(Error& error, const std::ios& status) noexcept
{
    return FailIfCreateFileError(error, status, "", nullptr, -1);
}

bool FailIfCreateFileError(Error& error, const std::ios& status, const std::string& path, const char* file,
    int line) noexcept
{
    if (!status.good())
    {
        Fail(error, IOErrorCategory::eCreateFileError, "failed to create file \'" + path + "\'", file, line);
        return true;
    }
    else
    {
        return false;
    }
}

bool FailIfOpenFileError(Error& error, const std::ios& status) noexcept
{
    return FailIfOpenFileError(error, status, "", nullptr, -1);
}

bool FailIfOpenFileError(Error& error, const std::ios& status, const std::string& path, const char* file,
    int line) noexcept
{
    if (!status.good())
    {
        Fail(error, IOErrorCategory::eOpenFileError, "failed to open file \'" + path + "\'", file, line);
        return true;
    }
    else
    {
        return false;
    }
}

}
