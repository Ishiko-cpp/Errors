/*
    Copyright (c) 2020-2022 Xavier Leclercq
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

std::ostream& SuccessCategory::streamOut(int value, std::ostream& os) const
{
    os << "success";
    return os;
}
