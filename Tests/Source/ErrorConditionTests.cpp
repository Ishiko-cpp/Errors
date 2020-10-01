/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "ErrorConditionTests.h"
#include "Helpers/TestErrorCategory1.h"
#include "Ishiko/Errors/ErrorCondition.h"
#include "Ishiko/Errors/SuccessCategory.h"

using namespace Ishiko::Tests;

ErrorConditionTests::ErrorConditionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ErrorCondition tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("succeed test 1", SucceedTest1);
}

void ErrorConditionTests::ConstructorTest1(Test& test)
{
    Ishiko::ErrorCondition error;

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(error.value(), 0);
    ISHTF_PASS();
}

void ErrorConditionTests::ConstructorTest2(Test& test)
{
    Ishiko::ErrorCondition error(0, Ishiko::SuccessCategory::Get());

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(error.value(), 0);
    ISHTF_PASS();
}

void ErrorConditionTests::ConstructorTest3(Test& test)
{
    Ishiko::ErrorCondition error(-1, TestErrorCategory1::Get());

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.value(), -1);
    ISHTF_PASS();
}

void ErrorConditionTests::FailTest1(Test& test)
{
    Ishiko::ErrorCondition error;
    error.fail(-3, TestErrorCategory1::Get());

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.value(), -3);
    ISHTF_PASS();
}

void ErrorConditionTests::FailTest2(Test& test)
{
    Ishiko::ErrorCondition error(4, TestErrorCategory1::Get());
    error.fail(-3, TestErrorCategory1::Get());

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.value(), -3);
    ISHTF_PASS();
}

void ErrorConditionTests::SucceedTest1(Test& test)
{
    Ishiko::ErrorCondition error(-1, TestErrorCategory1::Get());
    error.succeed();

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(error.value(), 0);
    ISHTF_PASS();
}
