/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "ErrorExtension.h"

namespace Ishiko
{

void ErrorExtension::release() noexcept
{
    delete this;
}

bool ErrorExtension::tryGetOrigin(const char*& file, int& line) const noexcept
{
    return false;
}

void ErrorExtension::onFail(int code, const std::string& message, const char* file, int line) noexcept
{
    // Do nothing
}

std::ostream& ErrorExtension::operator<<(std::ostream& os) const
{
    // Do nothing
    return os;
}

}
