/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "ExceptionTests.h"
#include "Ishiko/Errors/Exception.h"

using namespace Ishiko::Tests;

ExceptionTests::ExceptionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Exception tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void ExceptionTests::ConstructorTest1(Test& test)
{
    Ishiko::Exception exception("description", "file", 5);

    ISHTF_FAIL_IF_STR_NEQ(exception.what(), "description");
    ISHTF_FAIL_IF_NEQ(exception.file(), "file");
    ISHTF_FAIL_IF_NEQ(exception.line(), 5);
    ISHTF_PASS();
}
