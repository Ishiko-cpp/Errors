/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorStringTests.hpp"
#include "Ishiko/Errors/ErrorString.hpp"

using namespace Ishiko;

ErrorStringTests::ErrorStringTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ErrorString tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void ErrorStringTests::ConstructorTest1(Test& test)
{
    ErrorString str;

    ISHIKO_TEST_PASS();
}
