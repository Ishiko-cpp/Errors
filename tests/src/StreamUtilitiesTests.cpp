/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "StreamUtilitiesTests.h"
#include "Ishiko/Errors/StreamUtilities.h"
#include <fstream>

using namespace Ishiko;
using namespace Ishiko::Tests;

StreamUtilitiesTests::StreamUtilitiesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "StreamUtilities tests", environment)
{
    append<HeapAllocationErrorsTest>("FailIfCreateFileError test 1", FailIfCreateFileErrorTest1);
    append<HeapAllocationErrorsTest>("FailIfCreateFileError test 2", FailIfCreateFileErrorTest2);
    append<HeapAllocationErrorsTest>("FailIfOpenFileError test 1", FailIfOpenFileErrorTest1);
    append<HeapAllocationErrorsTest>("FailIfOpenFileError test 2", FailIfOpenFileErrorTest2);
}

void StreamUtilitiesTests::FailIfCreateFileErrorTest1(Test& test)
{
    // We try to open the file instead of creating it because this is easier to implement and puts the stream in the
    // same state
    Ishiko::Error error;
    std::fstream file("doesnotexist");

    bool failed = FailIfCreateFileError(error, file);
  
    ISHTF_FAIL_IF_NOT(failed);
    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), -2);
    ISHTF_FAIL_IF_NEQ(&error.condition().category(), &IOErrorCategory::Get());

    std::string message;
    bool messsageFound = error.tryGetMessage(message);

    ISHTF_FAIL_IF(messsageFound);

    const char* originFile = nullptr;
    int originLine = -1;
    bool originFound = error.tryGetOrigin(originFile, originLine);

    ISHTF_FAIL_IF(originFound);
    ISHTF_PASS();
}

void StreamUtilitiesTests::FailIfCreateFileErrorTest2(Test& test)
{
    const char* path = "doesnotexist";

    // We try to open the file instead of creating it because this is easier to implement and puts the stream in the
    // same state
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    std::fstream file(path);

    bool failed = FailIfCreateFileError(error, file, path, "file1", 3);

    ISHTF_FAIL_IF_NOT(failed);
    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), -2);
    ISHTF_FAIL_IF_NEQ(&error.condition().category(), &IOErrorCategory::Get());

    std::string message;
    bool messsageFound = error.tryGetMessage(message);

    ISHTF_FAIL_IF_NOT(messsageFound);
    ISHTF_FAIL_IF_NEQ(message, "failed to create file 'doesnotexist'");

    const char* originFile = nullptr;
    int originLine = -1;
    bool origin = error.tryGetOrigin(originFile, originLine);

    ISHTF_FAIL_IF_NOT(origin);
    ISHTF_FAIL_IF_STR_NEQ(originFile, "file1");
    ISHTF_FAIL_IF_NEQ(originLine, 3);
    ISHTF_PASS();
}

void StreamUtilitiesTests::FailIfOpenFileErrorTest1(Test& test)
{
    Ishiko::Error error;
    std::fstream file("doesnotexist");

    bool failed = FailIfOpenFileError(error, file);

    ISHTF_FAIL_IF_NOT(failed);
    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), -3);
    ISHTF_FAIL_IF_NEQ(&error.condition().category(), &IOErrorCategory::Get());

    std::string message;
    bool messsageFound = error.tryGetMessage(message);

    ISHTF_FAIL_IF(messsageFound);

    const char* originFile = nullptr;
    int originLine = -1;
    bool originFound = error.tryGetOrigin(originFile, originLine);

    ISHTF_FAIL_IF(originFound);
    ISHTF_PASS();
}

void StreamUtilitiesTests::FailIfOpenFileErrorTest2(Test& test)
{
    const char* path = "doesnotexist";

    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    std::fstream file(path);

    bool failed = FailIfOpenFileError(error, file, path, "file1", 3);

    ISHTF_FAIL_IF_NOT(failed);
    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), -3);
    ISHTF_FAIL_IF_NEQ(&error.condition().category(), &IOErrorCategory::Get());

    std::string message;
    bool messsageFound = error.tryGetMessage(message);

    ISHTF_FAIL_IF_NOT(messsageFound);
    ISHTF_FAIL_IF_NEQ(message, "failed to open file 'doesnotexist'");

    const char* originFile = nullptr;
    int originLine = -1;
    bool origin = error.tryGetOrigin(originFile, originLine);

    ISHTF_FAIL_IF_NOT(origin);
    ISHTF_FAIL_IF_STR_NEQ(originFile, "file1");
    ISHTF_FAIL_IF_NEQ(originLine, 3);
    ISHTF_PASS();
}
