/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#include "StreamUtilitiesTests.h"
#include "Ishiko/Errors/StreamUtilities.h"
#include <fstream>

using namespace Ishiko;
using namespace Ishiko::Tests;

StreamUtilitiesTests::StreamUtilitiesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "StreamUtilities tests", environment)
{
    append<HeapAllocationErrorsTest>("FailOnFileCreationError test 1", FailOnFileCreationErrorTest1);
    append<HeapAllocationErrorsTest>("FailOnFileCreationError test 2", FailOnFileCreationErrorTest2);
    append<HeapAllocationErrorsTest>("FailOnFileOpeningError test 1", FailOnFileOpeningErrorTest1);
    append<HeapAllocationErrorsTest>("FailOnFileOpeningError test 2", FailOnFileOpeningErrorTest2);
}

void StreamUtilitiesTests::FailOnFileCreationErrorTest1(Test& test)
{
    // We try to open the file instead of creating it because this is easier to implement and puts the stream in the
    // same state
    Ishiko::Error error;
    std::fstream file("doesnotexist");

    bool failed = FailOnFileCreationError(error, file);
  
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

void StreamUtilitiesTests::FailOnFileCreationErrorTest2(Test& test)
{
    const char* path = "doesnotexist";

    // We try to open the file instead of creating it because this is easier to implement and puts the stream in the
    // same state
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    std::fstream file(path);

    bool failed = FailOnFileCreationError(error, file, path, "file1", 3);

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

void StreamUtilitiesTests::FailOnFileOpeningErrorTest1(Test& test)
{
    Ishiko::Error error;
    std::fstream file("doesnotexist");

    bool failed = FailOnFileOpeningError(error, file);

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

void StreamUtilitiesTests::FailOnFileOpeningErrorTest2(Test& test)
{
    const char* path = "doesnotexist";

    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    std::fstream file(path);

    bool failed = FailOnFileOpeningError(error, file, path, "file1", 3);

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
