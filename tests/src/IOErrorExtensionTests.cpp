/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "IOErrorExtensionTests.hpp"
#include "Ishiko/Errors/IOErrorExtension.hpp"
#include "Ishiko/Errors/Error.hpp"
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

    ISHIKO_PASS();
}

void IOErrorExtensionTests::FailTest1(Test& test)
{
    Ishiko::Error error;
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF, "file1", 3);

    ISHIKO_FAIL_IF_NEQ(error.condition().value(), EIO);
    ISHIKO_FAIL_IF(error.extension());
    ISHIKO_PASS();
}

void IOErrorExtensionTests::FailTest2(Test& test)
{
    Ishiko::Error error(new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF, "file1", 3);

    ISHIKO_FAIL_IF_NEQ(error.condition().value(), EIO);

    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHIKO_ABORT_IF_NOT(ext);
    ISHIKO_FAIL_IF_NEQ(ext->code(), Ishiko::IOErrorExtension::eEOF);
    ISHIKO_PASS();
}

void IOErrorExtensionTests::FailTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");
    std::fstream file(inputPath.c_str());

    Ishiko::Error error;
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHIKO_FAIL_IF(error.extension());
    ISHIKO_PASS();
}

void IOErrorExtensionTests::FailTest4(Test& test)
{
    std::fstream file("doesnotexist");

    Ishiko::Error error;
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition().value(), EIO);
    ISHIKO_FAIL_IF(error.extension());
    ISHIKO_PASS();
}

void IOErrorExtensionTests::FailTest5(Test& test)
{
    std::fstream file("doesnotexist");

    Ishiko::Error error(new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHIKO_FAIL_IF_NEQ(error.condition().value(), EIO);
    
    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_ABORT_IF_NOT(ext);
    ISHIKO_FAIL_IF_NEQ(ext->code(), Ishiko::IOErrorExtension::eError);
    ISHIKO_PASS();
}

void IOErrorExtensionTests::FailTest6(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");
    std::fstream file(inputPath.c_str());
    char buffer[20];
    file.read(buffer, 20);

    Ishiko::Error error(new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, file, "file1", 3);

    ISHIKO_FAIL_IF_NEQ(error.condition().value(), EIO);

    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_ABORT_IF_NOT(ext);
    ISHIKO_FAIL_IF_NEQ(ext->code(), Ishiko::IOErrorExtension::eEOF);
    ISHIKO_PASS();
}

void IOErrorExtensionTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error(new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF, "file1", 3);

    std::stringstream errorMessage;
    errorMessage << error;

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(errorMessage.str(), "Ishiko::IOErrorCategory, 5, I/O error: end-of-file [file: file1, line: 3]");
    ISHIKO_PASS();
}
