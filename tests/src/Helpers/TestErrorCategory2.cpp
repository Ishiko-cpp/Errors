/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "TestErrorCategory2.h"

const TestErrorCategory2& TestErrorCategory2::Get() noexcept
{
    static TestErrorCategory2 theTestErrorCategory2;
    return theTestErrorCategory2;
}

const char* TestErrorCategory2::name() const noexcept
{
    return "TestErrorCategory2";
}
