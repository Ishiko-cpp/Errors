/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorCategory.hpp"
#include "Error.hpp"

using namespace Ishiko;

std::ostream& ErrorCategory::streamOut(const Error& error, std::ostream& os) const
{
    return streamOut(error.condition().value(), os);
}
