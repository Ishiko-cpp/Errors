/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "MessageErrorExtensionTests.h"
#include "Helpers/TestErrorCategory1.h"
#include "Ishiko/Errors/MessageErrorExtension.h"
#include "Ishiko/Errors/Error.h"
#include <sstream>

using namespace Ishiko::Tests;

MessageErrorExtensionTests::MessageErrorExtensionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "MessageErrorExtension tests", environment)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("operator<< test 1", StreamInsertionTest1);
}

void MessageErrorExtensionTests::ConstructorTest1(Test& test)
{
    Ishiko::MessageErrorExtension messageExtension;

    ISHTF_FAIL_IF_NEQ(messageExtension.message(), "");
    ISHTF_FAIL_IF_NEQ(messageExtension.file(), "");
    ISHTF_FAIL_IF_NEQ(messageExtension.line(), -1);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::ConstructorTest2(Test& test)
{
    Ishiko::MessageErrorExtension messageExtension("unknown", "file1", 3);

    ISHTF_FAIL_IF_NEQ(messageExtension.message(), "unknown");
    ISHTF_FAIL_IF_NEQ(messageExtension.file(), "file1");
    ISHTF_FAIL_IF_NEQ(messageExtension.line(), 3);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::FailTest1(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    Ishiko::MessageErrorExtension* messageExtension = static_cast<Ishiko::MessageErrorExtension*>(error.extension());

    ISHTF_ABORT_IF_NOT(messageExtension);
    ISHTF_FAIL_IF_NEQ(messageExtension->message(), "a bad error");
    ISHTF_FAIL_IF_NEQ(messageExtension->file(), "file1");
    ISHTF_FAIL_IF_NEQ(messageExtension->line(), 3);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::FailTest2(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);
    error.fail(-4, TestErrorCategory1::Get(), "another bad error", "file2", 6);

    Ishiko::MessageErrorExtension* messageExtension = static_cast<Ishiko::MessageErrorExtension*>(error.extension());

    ISHTF_ABORT_IF_NOT(messageExtension);
    ISHTF_FAIL_IF_NEQ(messageExtension->message(), "a bad error");
    ISHTF_FAIL_IF_NEQ(messageExtension->file(), "file1");
    ISHTF_FAIL_IF_NEQ(messageExtension->line(), 3);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_IF_NEQ(errorMessage.str(), "TestErrorCategory1, -3, a bad error [file: file1, line: 3]");
    ISHTF_PASS();
}
