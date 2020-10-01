/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "MessageErrorExtensionTests.h"
#include "Ishiko/Errors/MessageErrorExtension.h"
#include "Ishiko/Errors/Error.h"
#include <sstream>

using namespace Ishiko::Tests;

MessageErrorExtensionTests::MessageErrorExtensionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "MessageErrorExtension tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("Construction test 2", ConstructionTest2);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("operator<< test 1", StreamInsertionTest1);
}

void MessageErrorExtensionTests::ConstructionTest1(Test& test)
{
    Ishiko::MessageErrorExtension messageExtension;

    ISHTF_FAIL_IF_NEQ(messageExtension.message(), "");
    ISHTF_FAIL_IF_NEQ(messageExtension.file(), "");
    ISHTF_FAIL_IF_NEQ(messageExtension.line(), -1);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::ConstructionTest2(Test& test)
{
    Ishiko::MessageErrorExtension messageExtension("unknown", "file1", 3);

    ISHTF_FAIL_IF_NEQ(messageExtension.message(), "unknown");
    ISHTF_FAIL_IF_NEQ(messageExtension.file(), "file1");
    ISHTF_FAIL_IF_NEQ(messageExtension.line(), 3);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::FailTest1(Test& test)
{
    Ishiko::Error error(0, new Ishiko::MessageErrorExtension());
    error.fail(-3, "a bad error", "file1", 3);

    Ishiko::MessageErrorExtension* messageExtension = static_cast<Ishiko::MessageErrorExtension*>(error.extension());

    ISHTF_ABORT_IF_NOT(messageExtension);
    ISHTF_FAIL_IF_NEQ(messageExtension->message(), "a bad error");
    ISHTF_FAIL_IF_NEQ(messageExtension->file(), "file1");
    ISHTF_FAIL_IF_NEQ(messageExtension->line(), 3);
    ISHTF_PASS();
}

void MessageErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error(0, new Ishiko::MessageErrorExtension());
    error.fail(-3, "a bad error", "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_IF_NEQ(errorMessage.str(), "Error: -3, a bad error [file: file1, line: 3]");
    ISHTF_PASS();
}
