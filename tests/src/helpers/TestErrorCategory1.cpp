/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "TestErrorCategory1.hpp"

const TestErrorCategory1& TestErrorCategory1::Get() noexcept
{
    static TestErrorCategory1 theTestErrorCategory1;
    return theTestErrorCategory1;
}

const char* TestErrorCategory1::name() const noexcept
{
    return "TestErrorCategory1";
}

std::ostream& TestErrorCategory1::streamOut(int value, std::ostream& os) const
{
    os << "generic error";
    return os;
}
