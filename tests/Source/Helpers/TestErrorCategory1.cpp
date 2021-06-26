/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "TestErrorCategory1.h"

const TestErrorCategory1& TestErrorCategory1::Get() noexcept
{
    static TestErrorCategory1 theTestErrorCategory1;
    return theTestErrorCategory1;
}

const char* TestErrorCategory1::name() const noexcept
{
    return "TestErrorCategory1";
}
