/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ExceptionTests.h"
#include "Helpers/TestErrorCategory1.h"
#include "Ishiko/Errors/Exception.h"

using namespace Ishiko::Tests;

ExceptionTests::ExceptionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Exception tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("Constructor test 4", ConstructorTest4);
    append<HeapAllocationErrorsTest>("Constructor test 5", ConstructorTest5);
}

void ExceptionTests::ConstructorTest1(Test& test)
{
    Ishiko::ErrorCondition condition(-1, TestErrorCategory1::Get());
    Ishiko::Exception exception(condition, "file", 5);

    ISHTF_FAIL_IF_NEQ(exception.condition().value(), -1);
    ISHTF_FAIL_IF_STR_NEQ(exception.what(), "");
    ISHTF_FAIL_IF_NEQ(exception.file(), "file");
    ISHTF_FAIL_IF_NEQ(exception.line(), 5);
    ISHTF_PASS();
}

void ExceptionTests::ConstructorTest2(Test& test)
{
    Ishiko::Exception exception(-1, TestErrorCategory1::Get(), "file", 5);

    ISHTF_FAIL_IF_NEQ(exception.condition().value(), -1);
    ISHTF_FAIL_IF_STR_NEQ(exception.what(), "");
    ISHTF_FAIL_IF_NEQ(exception.file(), "file");
    ISHTF_FAIL_IF_NEQ(exception.line(), 5);
    ISHTF_PASS();
}

void ExceptionTests::ConstructorTest3(Test& test)
{
    Ishiko::Exception exception(-1, TestErrorCategory1::Get(), "description", "file", 5);

    ISHTF_FAIL_IF_NEQ(exception.condition().value(), -1);
    ISHTF_FAIL_IF_STR_NEQ(exception.what(), "description");
    ISHTF_FAIL_IF_NEQ(exception.file(), "file");
    ISHTF_FAIL_IF_NEQ(exception.line(), 5);
    ISHTF_PASS();
}

void ExceptionTests::ConstructorTest4(Test& test)
{
    Ishiko::Exception exception1(-1, TestErrorCategory1::Get(), "file", 5);
    Ishiko::Exception exception2(exception1);

    ISHTF_FAIL_IF_NEQ(exception2.condition().value(), -1);
    ISHTF_FAIL_IF_STR_NEQ(exception2.what(), "");
    ISHTF_FAIL_IF_NEQ(exception2.file(), "file");
    ISHTF_FAIL_IF_NEQ(exception2.line(), 5);
    ISHTF_PASS();
}

void ExceptionTests::ConstructorTest5(Test& test)
{
    Ishiko::Exception exception1(-1, TestErrorCategory1::Get(), "description", "file", 5);
    Ishiko::Exception exception2(exception1);

    ISHTF_FAIL_IF_NEQ(exception2.condition().value(), -1);
    ISHTF_FAIL_IF_STR_NEQ(exception2.what(), "description");
    ISHTF_FAIL_IF_NEQ(exception2.file(), "file");
    ISHTF_FAIL_IF_NEQ(exception2.line(), 5);
    ISHTF_PASS();
}
