/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "InfoErrorExtensionTests.hpp"
#include "helpers/TestErrorCategory1.hpp"
#include "Ishiko/Errors/Error.hpp"
#include "Ishiko/Errors/InfoErrorExtension.hpp"
#include <sstream>

using namespace Ishiko;

InfoErrorExtensionTests::InfoErrorExtensionTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "InfoErrorExtension tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("Constructor test 4", ConstructorTest4);
    append<HeapAllocationErrorsTest>("Set test 1", SetTest1);
    append<HeapAllocationErrorsTest>("Set test 2", SetTest2);
    append<HeapAllocationErrorsTest>("Set test 3", SetTest3);
    append<HeapAllocationErrorsTest>("Set test 4", SetTest4);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("operator<< test 1", StreamInsertionTest1);
}

void InfoErrorExtensionTests::ConstructorTest1(Test& test)
{
    InfoErrorExtension infoExtension;

    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.message(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.file(), "");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.line(), -1);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::ConstructorTest2(Test& test)
{
    InfoErrorExtension infoExtension("unknown", "file1", 3);

    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.message(), "unknown");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.line(), 3);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::ConstructorTest3(Test& test)
{
    InfoErrorExtension infoExtension("erreur syst\xC3\xA8me", "file1", 3);

    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.message(), "erreur syst\xC3\xA8me");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.line(), 3);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::ConstructorTest4(Test& test)
{
    InfoErrorExtension infoExtension(L"erreur syst\xE8me", "file1", 3);

    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.message(), "erreur syst\xC3\xA8me");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension.line(), 3);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::SetTest1(Test& test)
{
    Error error;

    InfoErrorExtension::Set(error, "message", "file1", 3);

    const InfoErrorExtension* infoExtension;
    bool found = error.extensions().tryGet(infoExtension);

    ISHIKO_TEST_FAIL_IF(found);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::SetTest2(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();

    InfoErrorExtension::Set(error, "system error", "file1", 3);

    const InfoErrorExtension* infoExtension;
    bool found = error.extensions().tryGet(infoExtension);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->message(), "system error");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->line(), 3);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::SetTest3(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();

    InfoErrorExtension::Set(error, "erreur syst\xC3\xA8me", "file1", 3);

    const InfoErrorExtension* infoExtension;
    bool found = error.extensions().tryGet(infoExtension);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->message(), "erreur syst\xC3\xA8me");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->line(), 3);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::SetTest4(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();

    InfoErrorExtension::Set(error, L"erreur syst\xE8me", "file1", 3);

    const InfoErrorExtension* infoExtension;
    bool found = error.extensions().tryGet(infoExtension);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->message(), "erreur syst\xC3\xA8me");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->line(), 3);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::FailTest1(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(TestErrorCategory1::Get(), -3, "a bad error", "file1", 3);

    const InfoErrorExtension* infoExtension;
    bool found = error.extensions().tryGet(infoExtension);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->message(), "a bad error");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->line(), 3);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::FailTest2(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(TestErrorCategory1::Get(), -3, "a bad error", "file1", 3);
    error.fail(TestErrorCategory1::Get(), -4, "another bad error", "file2", 6);

    const InfoErrorExtension* infoExtension;
    bool found = error.extensions().tryGet(infoExtension);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->message(), "a bad error");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->file(), "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(infoExtension->line(), 3);
    ISHIKO_TEST_PASS();
}

void InfoErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(TestErrorCategory1::Get(), -3, "a bad error", "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHIKO_TEST_FAIL_IF_NEQ(errorMessage.str(),
        "TestErrorCategory1 -3 (generic error), a bad error [file: file1, line: 3]");
    ISHIKO_TEST_PASS();
}
