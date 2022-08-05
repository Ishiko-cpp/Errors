/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorMessageTests.hpp"
#include "Ishiko/Errors/ErrorMessage.hpp"

using namespace Ishiko;

ErrorMessageTests::ErrorMessageTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ErrorMessage tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void ErrorMessageTests::ConstructorTest1(Test& test)
{
    ErrorMessage message;

    ISHIKO_TEST_PASS();
}
