/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "SuccessCategory.hpp"

using namespace Ishiko;

const SuccessCategory& SuccessCategory::Get() noexcept
{
    static SuccessCategory theCategory;
    return theCategory;
}

const char* SuccessCategory::name() const noexcept
{
    return "Ishiko::SuccessCategory";
}

const char* SuccessCategory::message(int ev, char* buffer, size_t len) const noexcept
{
    return ((ev == 0) ? "success" : "unknown value");
}
