/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "MessageErrorExtensionTests.hpp"
#include "helpers/TestErrorCategory1.hpp"
#include "Ishiko/Errors/Error.hpp"
#include "Ishiko/Errors/InfoErrorExtension.hpp"
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
    InfoErrorExtension infoExtension;

    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.message(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.file(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.line(), -1);
    ISHIKO_TEST_PASS();
}

void MessageErrorExtensionTests::ConstructorTest2(Test& test)
{
    InfoErrorExtension infoExtension("unknown", "file1", 3);

    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.message(), "unknown");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.line(), 3);
    ISHIKO_TEST_PASS();
}

void MessageErrorExtensionTests::FailTest1(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    const InfoErrorExtension* infoExtension;
    bool found = error.extensions().tryGet(infoExtension);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->message(), "a bad error");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->line(), 3);
    ISHIKO_TEST_PASS();
}

void MessageErrorExtensionTests::FailTest2(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);
    error.fail(-4, TestErrorCategory1::Get(), "another bad error", "file2", 6);

    const InfoErrorExtension* infoExtension;
    bool found = error.extensions().tryGet(infoExtension);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->message(), "a bad error");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->line(), 3);
    ISHIKO_TEST_PASS();
}

void MessageErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHIKO_TEST_FAIL_IF_NEQ(errorMessage.str(), "TestErrorCategory1, -3, a bad error [file: file1, line: 3]");
    ISHIKO_TEST_PASS();
}
