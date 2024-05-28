/*
    Copyright (c) 2022-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorCategory.hpp"
#include "Error.hpp"

using namespace Ishiko;

std::string ErrorCategory::message(int ev) const
{
    return message(ev, nullptr, 0);
}
