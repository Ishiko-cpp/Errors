/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
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
    Ishiko::Error error;
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF, "file1", 3);

    ISHTF_FAIL_IF_NEQ(error.condition().value(), EIO);
    ISHTF_FAIL_IF(error.extension());
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest2(Test& test)
{
    Ishiko::Error error(new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF, "file1", 3);

    ISHTF_FAIL_IF_NEQ(error.condition().value(), EIO);

    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHTF_ABORT_IF_NOT(ext);
    ISHTF_FAIL_IF_NEQ(ext->code(), Ishiko::IOErrorExtension::eEOF);
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");
    std::fstream file(inputPath.c_str());

    Ishiko::Error error(0);
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHTF_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHTF_FAIL_IF(error.extension());
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest4(Test& test)
{
    std::fstream file("doesnotexist");

    Ishiko::Error error(0);
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHTF_FAIL_IF_NEQ(error.condition().value(), EIO);
    ISHTF_FAIL_IF(error.extension());
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest5(Test& test)
{
    std::fstream file("doesnotexist");

    Ishiko::Error error(new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHTF_FAIL_IF_NEQ(error.condition().value(), EIO);
    
    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHTF_ABORT_IF_NOT(ext);
    ISHTF_FAIL_IF_NEQ(ext->code(), Ishiko::IOErrorExtension::eError);
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest6(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");
    std::fstream file(inputPath.c_str());
    char buffer[20];
    file.read(buffer, 20);

    Ishiko::Error error(new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHTF_FAIL_IF_NEQ(error.condition().value(), EIO);

    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHTF_ABORT_IF_NOT(ext);
    ISHTF_FAIL_IF_NEQ(ext->code(), Ishiko::IOErrorExtension::eEOF);
    ISHTF_PASS();
}

void IOErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error(new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF, "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHTF_FAIL_IF_NEQ(errorMessage.str(), "Ishiko::IOErrorCategory, 5, I/O error: end-of-file [file: file1, line: 3]");
    ISHTF_PASS();
}
