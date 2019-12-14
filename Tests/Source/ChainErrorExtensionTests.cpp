/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "ChainErrorExtensionTests.h"
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
    Ishiko::Error error(0, new Ishiko::ChainErrorExtension());
    error.fail(-3, "a bad error", "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_IF_NEQ(errorMessage.str(), "Error: -3, a bad error [file: file1, line: 3]");
    ISHTF_PASS();
}

void ChainErrorExtensionTests::StreamInsertionTest2(Test& test)
{
    Ishiko::Error error(0, new Ishiko::ChainErrorExtension());
    error.fail(-3, "a bad error", "file1", 3);
    error.fail(-1);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_IF_NEQ(errorMessage.str(), "Error: -3, a bad error [file: file1, line: 3]\n\tError: -1");
    ISHTF_PASS();
}
