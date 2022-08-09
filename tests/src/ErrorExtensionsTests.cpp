/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorExtensionsTests.hpp"
#include "Ishiko/Errors/Error.hpp"

using namespace Ishiko;

ErrorExtensionsTests::ErrorExtensionsTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Error::Extensions tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void ErrorExtensionsTests::ConstructorTest1(Test& test)
{
    Error::Extension extensions;

    ISHIKO_TEST_PASS();
}
