/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "IOErrorCategory.h"

namespace Ishiko
{

const IOErrorCategory& IOErrorCategory::Get() noexcept
{
    static IOErrorCategory theCategory;
    return theCategory;
}

const char* IOErrorCategory::name() const noexcept
{
    return "Ishiko::IOErrorCategory";
}

void Fail(Error& error, IOErrorCategory::EErrorValues value) noexcept
{
    error.fail(value, IOErrorCategory::Get());
}

void Fail(Error& error, IOErrorCategory::EErrorValues value, const std::string& message, const char* file,
    int line) noexcept
{
    error.fail(value, IOErrorCategory::Get(), message, file, line);
}


}
