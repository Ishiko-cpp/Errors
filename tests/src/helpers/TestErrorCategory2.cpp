/*
    Copyright (c) 2021-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "TestErrorCategory2.hpp"

const TestErrorCategory2& TestErrorCategory2::Get() noexcept
{
    static TestErrorCategory2 theTestErrorCategory2;
    return theTestErrorCategory2;
}

const char* TestErrorCategory2::name() const noexcept
{
    return "TestErrorCategory2";
}

const char* TestErrorCategory2::message(int ev, char* buffer, size_t len) const noexcept
{
    return "generic error";
}
