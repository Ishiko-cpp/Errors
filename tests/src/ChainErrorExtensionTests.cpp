/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ChainErrorExtensionTests.h"
#include "Helpers/TestErrorCategory1.h"
#include "Ishiko/Errors/ChainErrorExtension.h"
#include "Ishiko/Errors/Error.h"
#include <sstream>

using namespace Ishiko::Tests;

ChainErrorExtensionTests::ChainErrorExtensionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "ChainErrorExtension tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("operator<< test 1", StreamInsertionTest1);
    append<HeapAllocationErrorsTest>("operator<< test 2", StreamInsertionTest2);
}

void ChainErrorExtensionTests::ConstructionTest1(Test& test)
{
    Ishiko::ChainErrorExtension chainExtension;

    ISHTF_PASS();
}

void ChainErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error(new Ishiko::ChainErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_IF_NEQ(errorMessage.str(), "TestErrorCategory1, -3, a bad error [file: file1, line: 3]");
    ISHTF_PASS();
}

void ChainErrorExtensionTests::StreamInsertionTest2(Test& test)
{
    Ishiko::Error error(new Ishiko::ChainErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);
    error.fail(-1, TestErrorCategory1::Get());

    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_IF_NEQ(errorMessage.str(), "TestErrorCategory1, -3, a bad error [file: file1, line: 3]\n\tError: -1");
    ISHTF_PASS();
}
