/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorTests.hpp"
#include "helpers/TestErrorCategory1.hpp"
#include "helpers/TestErrorCategory2.hpp"
#include "helpers/TestErrorExtension.hpp"
#include "Ishiko/Errors/Error.hpp"
#include "Ishiko/Errors/Exception.hpp"
#include "Ishiko/Errors/InfoErrorExtension.hpp"
#include "Ishiko/Errors/SuccessCategory.hpp"
#include <sstream>

using namespace Ishiko;

ErrorTests::ErrorTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Error tests", context)
{
    append<HeapAllocationErrorsTest>("install test 1", ExtensionsInstallTest1);
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("operator==() test 1", EqualityOperatorTest1);
    append<HeapAllocationErrorsTest>("operator==() test 2", EqualityOperatorTest2);
    append<HeapAllocationErrorsTest>("operator!=() test 1", InequalityOperatorTest1);
    append<HeapAllocationErrorsTest>("operator!=() test 2", InequalityOperatorTest2);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("fail test 3", FailTest3);
    append<HeapAllocationErrorsTest>("clear test 1", ClearTest1);
    append<HeapAllocationErrorsTest>("operator<< test 1", StreamInsertionTest1);
    append<HeapAllocationErrorsTest>("tryGetMessage test 1", TryGetMessageTest1);
    append<HeapAllocationErrorsTest>("tryGetMessage test 2", TryGetMessageTest2);
    append<HeapAllocationErrorsTest>("tryGetMessage test 3", TryGetMessageTest3);
    append<HeapAllocationErrorsTest>("tryGetMessage test 4", TryGetMessageTest4);
    append<HeapAllocationErrorsTest>("tryGetOrigin test 1", TryGetOriginTest1);
    append<HeapAllocationErrorsTest>("tryGetOrigin test 2", TryGetOriginTest2);
    append<HeapAllocationErrorsTest>("tryGetOrigin test 3", TryGetOriginTest3);
    append<HeapAllocationErrorsTest>("tryGetOrigin test 4", TryGetOriginTest4);
    append<HeapAllocationErrorsTest>("ThrowIf test 1", ThrowIfTest1);
    append<HeapAllocationErrorsTest>("ThrowIf test 2", ThrowIfTest2);
    append<HeapAllocationErrorsTest>("ThrowIf test 3", ThrowIfTest3);
}

void ErrorTests::ExtensionsInstallTest1(Test& test)
{
    Error::Extensions extensions;

    ErrorCondition err = extensions.install<TestErrorExtension>();

    ISHIKO_TEST_FAIL_IF(err);

    const TestErrorExtension* extension;
    bool found = extensions.tryGet(extension);

    ISHIKO_TEST_FAIL_IF_NOT(extension);
    ISHIKO_TEST_PASS();
}

void ErrorTests::ConstructorTest1(Test& test)
{
    Error error;

    ISHIKO_TEST_FAIL_IF_NEQ(sizeof(error), 24);
    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(&error.condition().category(), &Ishiko::SuccessCategory::Get());
    ISHIKO_TEST_PASS();
}

void ErrorTests::ConstructorTest2(Test& test)
{
    Error error{TestErrorCategory1::Get(), -2};
    
    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.condition().value(), -2);
    ISHIKO_TEST_FAIL_IF_NEQ(&error.condition().category(), &TestErrorCategory1::Get());
    ISHIKO_TEST_PASS();
}

void ErrorTests::EqualityOperatorTest1(Test& test)
{
    Error error1{TestErrorCategory1::Get(), -1};
    ErrorCondition error2{TestErrorCategory1::Get(), -1};

    ISHIKO_TEST_FAIL_IF_NOT(error1 == error2);
    ISHIKO_TEST_PASS();
}

void ErrorTests::EqualityOperatorTest2(Test& test)
{
    Error error1{TestErrorCategory1::Get(), -1};
    ErrorCondition error2{TestErrorCategory1::Get(), -3};

    ISHIKO_TEST_FAIL_IF(error1 == error2);

    Error error3{TestErrorCategory1::Get(), -1};
    ErrorCondition error4{TestErrorCategory2::Get(), -1};

    ISHIKO_TEST_FAIL_IF(error3 == error4);

    ISHIKO_TEST_PASS();
}

void ErrorTests::InequalityOperatorTest1(Test& test)
{
    Error error1{TestErrorCategory1::Get(), -1};
    ErrorCondition error2{TestErrorCategory1::Get(), -1};

    ISHIKO_TEST_FAIL_IF(error1 != error2);
    ISHIKO_TEST_PASS();
}

void ErrorTests::InequalityOperatorTest2(Test& test)
{
    Error error1{TestErrorCategory1::Get(), -1};
    ErrorCondition error2{TestErrorCategory1::Get(), -3};

    ISHIKO_TEST_FAIL_IF_NOT(error1 != error2);

    Error error3{TestErrorCategory1::Get(), -1};
    ErrorCondition error4{TestErrorCategory2::Get(), -1};

    ISHIKO_TEST_FAIL_IF_NOT(error3 != error4);

    ISHIKO_TEST_PASS();
}

void ErrorTests::FailTest1(Test& test)
{
    Error error;
    error.fail(TestErrorCategory1::Get(), -3);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.condition().value(), -3);
    ISHIKO_TEST_FAIL_IF_NEQ(&error.condition().category(), &TestErrorCategory1::Get());
    ISHIKO_TEST_PASS();
}

void ErrorTests::FailTest2(Test& test)
{
    Error error{TestErrorCategory1::Get(), 4};
    error.fail(TestErrorCategory1::Get(), -3);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.condition().value(), 4);
    ISHIKO_TEST_FAIL_IF_NEQ(&error.condition().category(), &TestErrorCategory1::Get());
    ISHIKO_TEST_PASS();
}

void ErrorTests::FailTest3(Test& test)
{
    Error error1{TestErrorCategory1::Get(), 4};

    Error error2;
    error2.fail(error1);

    ISHIKO_TEST_FAIL_IF_NOT(error2);
    ISHIKO_TEST_FAIL_IF_NEQ(error2.condition().value(), 4);
    ISHIKO_TEST_FAIL_IF_NEQ(&error2.condition().category(), &TestErrorCategory1::Get());
    ISHIKO_TEST_PASS();
}

void ErrorTests::ClearTest1(Test& test)
{
    Error error{TestErrorCategory1::Get(), -1};
    error.clear();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHIKO_TEST_FAIL_IF_NEQ(&error.condition().category(), &SuccessCategory::Get());
    ISHIKO_TEST_PASS();
}

void ErrorTests::StreamInsertionTest1(Test& test)
{
    Error error;
    
    std::stringstream errorMessage;
    errorMessage << error;

    ISHIKO_TEST_FAIL_IF_NEQ(errorMessage.str(), "Ishiko::SuccessCategory, 0");
    ISHIKO_TEST_PASS();
}

void ErrorTests::TryGetMessageTest1(Test& test)
{
    Error error;

    std::string message;
    bool found = error.tryGetMessage(message);

    ISHIKO_TEST_FAIL_IF(found);
    ISHIKO_TEST_PASS();
}

void ErrorTests::TryGetMessageTest2(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();

    std::string message;
    bool found = error.tryGetMessage(message);

    ISHIKO_TEST_FAIL_IF(found);
    ISHIKO_TEST_PASS();
}

void ErrorTests::TryGetMessageTest3(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(TestErrorCategory1::Get(), -3);

    std::string message;
    bool found = error.tryGetMessage(message);

    ISHIKO_TEST_FAIL_IF(found);
    ISHIKO_TEST_PASS();
}

void ErrorTests::TryGetMessageTest4(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(TestErrorCategory1::Get(), -3, "a bad error", "file1", 3);

    std::string message;
    bool found = error.tryGetMessage(message);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(message, "a bad error");
    ISHIKO_TEST_PASS();
}

void ErrorTests::TryGetOriginTest1(Test& test)
{
    Error error;

    ErrorString file;
    int line = -1;
    bool found = error.tryGetOrigin(file, line);

    ISHIKO_TEST_FAIL_IF(found);
    ISHIKO_TEST_PASS();
}

void ErrorTests::TryGetOriginTest2(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();

    ErrorString file;
    int line = -1;
    bool found = error.tryGetOrigin(file, line);

    ISHIKO_TEST_FAIL_IF(found);
    ISHIKO_TEST_PASS();
}

void ErrorTests::TryGetOriginTest3(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(TestErrorCategory1::Get(), -3);

    ErrorString file;
    int line = -1;
    bool found = error.tryGetOrigin(file, line);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(file, "");
    ISHIKO_TEST_FAIL_IF_NEQ(line, -1);
    ISHIKO_TEST_PASS();
}

void ErrorTests::TryGetOriginTest4(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(TestErrorCategory1::Get(), -3, "a bad error", "file1", 3);

    ErrorString file;
    int line = -1;
    bool found = error.tryGetOrigin(file, line);

    ISHIKO_TEST_ABORT_IF_NOT(found);
    ISHIKO_TEST_FAIL_IF_NEQ(file, "file1");
    ISHIKO_TEST_FAIL_IF_NEQ(line, 3);
    ISHIKO_TEST_PASS();
}

void ErrorTests::ThrowIfTest1(Test& test)
{
    Error error;

    ThrowIf(error);

    ISHIKO_TEST_PASS();
}

void ErrorTests::ThrowIfTest2(Test& test)
{
    Error error{TestErrorCategory1::Get(), -1};

    try
    {
        ThrowIf(error);

        ISHIKO_TEST_FAIL();
    }
    catch (const Exception& e)
    {
        ISHIKO_TEST_FAIL_IF_NEQ(e.condition().value(), -1);
        ISHIKO_TEST_FAIL_IF_NEQ(&e.condition().category(), &TestErrorCategory1::Get());
        ISHIKO_TEST_PASS();
    }
}

void ErrorTests::ThrowIfTest3(Test& test)
{
    Error error;
    error.extensions().install<InfoErrorExtension>();
    error.fail(TestErrorCategory1::Get(), -1, "a bad error", "file1", 3);

    try
    {
        ThrowIf(error);

        ISHIKO_TEST_FAIL();
    }
    catch (const Exception& e)
    {
        ISHIKO_TEST_FAIL_IF_NEQ(e.condition().value(), -1);
        ISHIKO_TEST_FAIL_IF_NEQ(&e.condition().category(), &TestErrorCategory1::Get());
        ISHIKO_TEST_FAIL_IF_NEQ(e.file(), "file1");
        ISHIKO_TEST_FAIL_IF_NEQ(e.line(), 3);
        ISHIKO_TEST_PASS();
    }
}
