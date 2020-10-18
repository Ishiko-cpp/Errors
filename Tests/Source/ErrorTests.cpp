/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "ErrorTests.h"
#include "Helpers/TestErrorCategory1.h"
#include "Ishiko/Errors/Error.h"
#include "Ishiko/Errors/SuccessCategory.h"
#include "Ishiko/Errors/Exception.h"
#include <sstream>

using namespace Ishiko::Tests;

ErrorTests::ErrorTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Error tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("succeed test 1", SucceedTest1);
    append<HeapAllocationErrorsTest>("operator<< test 1", StreamInsertionTest1);
    append<HeapAllocationErrorsTest>("ThrowIf test 1", ThrowIfTest1);
    append<HeapAllocationErrorsTest>("ThrowIf test 2", ThrowIfTest2);
}

void ErrorTests::ConstructorTest1(Test& test)
{
    Ishiko::Error error;

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHTF_FAIL_IF_NEQ(&error.condition().category(), &Ishiko::SuccessCategory::Get());
    ISHTF_PASS();
}

void ErrorTests::ConstructorTest2(Test& test)
{
    Ishiko::Error error(-2, TestErrorCategory1::Get());
    
    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), -2);
    ISHTF_FAIL_IF_NEQ(&error.condition().category(), &TestErrorCategory1::Get());
    ISHTF_PASS();
}

void ErrorTests::FailTest1(Test& test)
{
    Ishiko::Error error;
    error.fail(-3, TestErrorCategory1::Get());

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), -3);
    ISHTF_FAIL_IF_NEQ(&error.condition().category(), &TestErrorCategory1::Get());
    ISHTF_PASS();
}

void ErrorTests::FailTest2(Test& test)
{
    Ishiko::Error error(4, TestErrorCategory1::Get());
    error.fail(-3, TestErrorCategory1::Get());

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), 4);
    ISHTF_FAIL_IF_NEQ(&error.condition().category(), &TestErrorCategory1::Get());
    ISHTF_PASS();
}

void ErrorTests::SucceedTest1(Test& test)
{
    Ishiko::Error error(-1, TestErrorCategory1::Get());
    error.succeed();

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHTF_FAIL_IF_NEQ(&error.condition().category(), &Ishiko::SuccessCategory::Get());
    ISHTF_PASS();
}

void ErrorTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error;
    
    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_IF_NEQ(errorMessage.str(), "Error: 0");
    ISHTF_PASS();
}

void ErrorTests::ThrowIfTest1(Test& test)
{
    Ishiko::Error error;

    ThrowIf(error);

    ISHTF_PASS();
}

void ErrorTests::ThrowIfTest2(Test& test)
{
    Ishiko::Error error(-1, TestErrorCategory1::Get());

    try
    {
        ThrowIf(error);

        ISHTF_FAIL();
    }
    catch (const Ishiko::Exception& e)
    {
        ISHTF_FAIL_IF_NEQ(e.condition().value(), -1);
        ISHTF_FAIL_IF_NEQ(&e.condition().category(), &TestErrorCategory1::Get());
        ISHTF_PASS();
    }
}
