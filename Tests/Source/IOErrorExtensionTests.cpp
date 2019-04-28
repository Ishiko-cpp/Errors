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

#include "IOErrorExtensionTests.h"
#include "Ishiko/Errors/IOErrorExtension.h"
#include "Ishiko/Errors/Error.h"
#include <sstream>
#include <fstream>
#include <errno.h>

using namespace Ishiko::Tests;

IOErrorExtensionTests::IOErrorExtensionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "IOErrorExtension tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("Fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("Fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("Fail test 3", FailTest3);
    append<HeapAllocationErrorsTest>("Fail test 4", FailTest4);
    append<HeapAllocationErrorsTest>("Fail test 5", FailTest5);
    append<HeapAllocationErrorsTest>("Fail test 6", FailTest6);
    append<HeapAllocationErrorsTest>("operator<< test 1", StreamInsertionTest1);
}

void IOErrorExtensionTests::ConstructionTest1(Test& test)
{
    Ishiko::IOErrorExtension ioExtension;

    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest1(Test& test)
{
    Ishiko::Error error(0);
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF, "file1", 3);

    ISHTF_FAIL_UNLESS(error.code() == EIO);
    ISHTF_FAIL_IF(error.extension());
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest2(Test& test)
{
    Ishiko::Error error(0, new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF, "file1", 3);

    ISHTF_FAIL_UNLESS(error.code() == EIO);

    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHTF_ABORT_UNLESS(ext);
    ISHTF_FAIL_UNLESS(ext->code() == Ishiko::IOErrorExtension::eEOF);
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");
    std::fstream file(inputPath.c_str());

    Ishiko::Error error(0);
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHTF_FAIL_UNLESS(error.code() == 0);
    ISHTF_FAIL_IF(error.extension());
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest4(Test& test)
{
    std::fstream file("doesnotexist");

    Ishiko::Error error(0);
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHTF_FAIL_UNLESS(error.code() == EIO);
    ISHTF_FAIL_IF(error.extension());
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest5(Test& test)
{
    std::fstream file("doesnotexist");

    Ishiko::Error error(0, new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHTF_FAIL_UNLESS(error.code() == EIO);
    
    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHTF_ABORT_UNLESS(ext);
    ISHTF_FAIL_UNLESS(ext->code() == Ishiko::IOErrorExtension::eError);
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest6(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");
    std::fstream file(inputPath.c_str());
    char buffer[20];
    file.read(buffer, 20);

    Ishiko::Error error(0, new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHTF_FAIL_UNLESS(error.code() == EIO);

    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHTF_ABORT_UNLESS(ext);
    ISHTF_FAIL_UNLESS(ext->code() == Ishiko::IOErrorExtension::eEOF);
    ISHTF_PASS();
}

void IOErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error(0, new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF, "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_UNLESS(errorMessage.str() == "Error: 5, I/O error: end-of-file [file: file1, line: 3]");
    ISHTF_PASS();
}
