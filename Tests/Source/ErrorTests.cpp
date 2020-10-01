/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "ErrorTests.h"
#include "Ishiko/Errors/Error.h"
#include "Ishiko/Errors/Exception.h"
#include <sstream>

using namespace Ishiko::Tests;

ErrorTests::ErrorTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Error tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("Construction test 2", ConstructionTest2);
    append<HeapAllocationErrorsTest>("Construction test 3", ConstructionTest3);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("succeed test 1", SucceedTest1);
    append<HeapAllocationErrorsTest>("operator<< test 1", StreamInsertionTest1);
}

void ErrorTests::ConstructionTest1(Test& test)
{
    Ishiko::Error error;

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), -1);
    ISHTF_PASS();
}

void ErrorTests::ConstructionTest2(Test& test)
{
    Ishiko::Error error(0);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHTF_PASS();
}

void ErrorTests::ConstructionTest3(Test& test)
{
    Ishiko::Error error(-2);
    
    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), -2);
    ISHTF_PASS();
}

void ErrorTests::FailTest1(Test& test)
{
    Ishiko::Error error(0);
    error.fail(-3);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), -3);
    ISHTF_PASS();
}

void ErrorTests::FailTest2(Test& test)
{
    Ishiko::Error error(4);
    error.fail(-3);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), 4);
    ISHTF_PASS();
}

void ErrorTests::SucceedTest1(Test& test)
{
    Ishiko::Error error;
    error.succeed();

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHTF_PASS();
}

void ErrorTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error;
    
    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_IF_NEQ(errorMessage.str(), "Error: -1");
    ISHTF_PASS();
}
