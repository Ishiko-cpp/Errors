/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "SuccessCategory.hpp"

namespace Ishiko
{

const SuccessCategory& SuccessCategory::Get() noexcept
{
    static SuccessCategory theCategory;
    return theCategory;
}

const char* SuccessCategory::name() const noexcept
{
    return "Ishiko::SuccessCategory";
}

}
