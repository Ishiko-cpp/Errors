/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "MessageErrorExtensionTests.hpp"
#include "Helpers/TestErrorCategory1.hpp"
#include "Ishiko/Errors/MessageErrorExtension.hpp"
#include "Ishiko/Errors/Error.hpp"
#include <sstream>

using namespace Ishiko;

MessageErrorExtensionTests::MessageErrorExtensionTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "MessageErrorExtension tests", context)
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

    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension.message(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension.file(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension.line(), -1);
    ISHIKO_TEST_PASS();
}

void MessageErrorExtensionTests::ConstructorTest2(Test& test)
{
    Ishiko::MessageErrorExtension messageExtension("unknown", "file1", 3);

    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension.message(), "unknown");
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension.file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension.line(), 3);
    ISHIKO_TEST_PASS();
}

void MessageErrorExtensionTests::FailTest1(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    Ishiko::MessageErrorExtension* messageExtension = static_cast<Ishiko::MessageErrorExtension*>(error.extension());

    ISHIKO_TEST_ABORT_IF_NOT(messageExtension);
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension->message(), "a bad error");
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension->file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension->line(), 3);
    ISHIKO_TEST_PASS();
}

void MessageErrorExtensionTests::FailTest2(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);
    error.fail(-4, TestErrorCategory1::Get(), "another bad error", "file2", 6);

    Ishiko::MessageErrorExtension* messageExtension = static_cast<Ishiko::MessageErrorExtension*>(error.extension());

    ISHIKO_TEST_ABORT_IF_NOT(messageExtension);
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension->message(), "a bad error");
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension->file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(messageExtension->line(), 3);
    ISHIKO_TEST_PASS();
}

void MessageErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHIKO_TEST_FAIL_IF_NEQ(errorMessage.str(), "TestErrorCategory1, -3, a bad error [file: file1, line: 3]");
    ISHIKO_TEST_PASS();
}
