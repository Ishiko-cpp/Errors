/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "SuccessCategory.h"

namespace Ishiko
{

const SuccessCategory& SuccessCategory::Get() noexcept
{
    static SuccessCategory theCategory;
    return theCategory;
}

}
