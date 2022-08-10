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

std::ostream& ErrorsErrorCategory::streamOut(int value, std::ostream& os) const
{
    switch (value)
    {
    case Value::generic_error:
        os << "generic error";
        break;

    case Value::memory_allocation_error:
        os << "memory allocation error";
        break;

    default:
        os << "unknown value";
        break;
    }
    return os;
}
