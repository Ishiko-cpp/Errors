/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "StreamUtilities.h"
#include "IOErrorCategory.h"

namespace Ishiko
{

bool FailOnFileCreationError(Error& error, const std::ios& status) noexcept
{
    return FailOnFileCreationError(error, status, "", nullptr, -1);
}

bool FailOnFileCreationError(Error& error, const std::ios& status, const std::string& path, const char* file,
    int line) noexcept
{
    if (!status.good())
    {
        Fail(error, IOErrorCategory::eCreationError, "Failed to create " + path, file, line);
        return true;
    }
    else
    {
        return false;
    }
}

}
