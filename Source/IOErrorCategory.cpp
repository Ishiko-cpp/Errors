/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "IOErrorCategory.h"

namespace Ishiko
{

namespace
{
    IOErrorCategory theIOErrorCategory;
}

const IOErrorCategory& IOErrorCategory::Get() noexcept
{
    return theIOErrorCategory;
}

}
