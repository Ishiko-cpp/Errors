/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "ErrorConditionTests.h"
#include "Ishiko/Errors/ErrorCondition.h"

using namespace Ishiko::Tests;

ErrorConditionTests::ErrorConditionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ErrorCondition tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructorTest1);
}

void ErrorConditionTests::ConstructorTest1(Test& test)
{
    Ishiko::ErrorCondition error;

    ISHTF_PASS();
}
