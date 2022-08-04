/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorExtension.hpp"

using namespace Ishiko;

void ErrorExtension::release() noexcept
{
    delete this;
}

std::ostream& ErrorExtension::operator<<(std::ostream& os) const
{
    // Do nothing
    return os;
}
