/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
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

}
