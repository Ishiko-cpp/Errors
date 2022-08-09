/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorsErrorCategory.hpp"

using namespace Ishiko;

const ErrorsErrorCategory& ErrorsErrorCategory::Get() noexcept
{
    static ErrorsErrorCategory theCategory;
    return theCategory;
}

const char* ErrorsErrorCategory::name() const noexcept
{
    return "Ishiko::ErrorsErrorCategory";
}
