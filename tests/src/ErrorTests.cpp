/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorTests.hpp"
#include "Helpers/TestErrorCategory1.hpp"
#include "Helpers/TestErrorCategory2.hpp"
#include "Ishiko/Errors/Error.hpp"
#include "Ishiko/Errors/SuccessCategory.hpp"
#include "Ishiko/Errors/MessageErrorExtension.hpp"
#include "Ishiko/Errors/Exception.hpp"
#include <sstream>

using namespace Ishiko::Tests;

ErrorTests::ErrorTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Error tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("operator==() test 1", EqualityOperatorTest1);
    append<HeapAllocationErrorsTest>("operator==() test 2", EqualityOperatorTest2);
    append<HeapAllocationErrorsTest>("operator!=() test 1", InequalityOperatorTest1);
    append<HeapAllocationErrorsTest>("operator!=() test 2", InequalityOperatorTest2);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("fail test 3", FailTest3);
    append<HeapAllocationErrorsTest>("succeed test 1", SucceedTest1);
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

void ErrorTests::ConstructorTest1(Test& test)
{
    Ishiko::Error error;

    ISHIKO_FAIL_IF_NEQ(sizeof(error), 24);
    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHIKO_FAIL_IF_NEQ(&error.condition().category(), &Ishiko::SuccessCategory::Get());
    ISHIKO_PASS();
}

void ErrorTests::ConstructorTest2(Test& test)
{
    Ishiko::Error error(-2, TestErrorCategory1::Get());
    
    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition().value(), -2);
    ISHIKO_FAIL_IF_NEQ(&error.condition().category(), &TestErrorCategory1::Get());
    ISHIKO_PASS();
}

void ErrorTests::EqualityOperatorTest1(Test& test)
{
    Ishiko::Error error1(-1, TestErrorCategory1::Get());
    Ishiko::ErrorCondition error2(-1, TestErrorCategory1::Get());

    ISHIKO_FAIL_IF_NOT(error1 == error2);
    ISHIKO_PASS();
}

void ErrorTests::EqualityOperatorTest2(Test& test)
{
    Ishiko::Error error1(-1, TestErrorCategory1::Get());
    Ishiko::ErrorCondition error2(-3, TestErrorCategory1::Get());

    ISHIKO_FAIL_IF(error1 == error2);

    Ishiko::Error error3(-1, TestErrorCategory1::Get());
    Ishiko::ErrorCondition error4(-1, TestErrorCategory2::Get());

    ISHIKO_FAIL_IF(error3 == error4);

    ISHIKO_PASS();
}

void ErrorTests::InequalityOperatorTest1(Test& test)
{
    Ishiko::Error error1(-1, TestErrorCategory1::Get());
    Ishiko::ErrorCondition error2(-1, TestErrorCategory1::Get());

    ISHIKO_FAIL_IF(error1 != error2);
    ISHIKO_PASS();
}

void ErrorTests::InequalityOperatorTest2(Test& test)
{
    Ishiko::Error error1(-1, TestErrorCategory1::Get());
    Ishiko::ErrorCondition error2(-3, TestErrorCategory1::Get());

    ISHIKO_FAIL_IF_NOT(error1 != error2);

    Ishiko::Error error3(-1, TestErrorCategory1::Get());
    Ishiko::ErrorCondition error4(-1, TestErrorCategory2::Get());

    ISHIKO_FAIL_IF_NOT(error3 != error4);

    ISHIKO_PASS();
}

void ErrorTests::FailTest1(Test& test)
{
    Ishiko::Error error;
    error.fail(-3, TestErrorCategory1::Get());

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition().value(), -3);
    ISHIKO_FAIL_IF_NEQ(&error.condition().category(), &TestErrorCategory1::Get());
    ISHIKO_PASS();
}

void ErrorTests::FailTest2(Test& test)
{
    Ishiko::Error error(4, TestErrorCategory1::Get());
    error.fail(-3, TestErrorCategory1::Get());

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition().value(), 4);
    ISHIKO_FAIL_IF_NEQ(&error.condition().category(), &TestErrorCategory1::Get());
    ISHIKO_PASS();
}

void ErrorTests::FailTest3(Test& test)
{
    Ishiko::Error error1(4, TestErrorCategory1::Get());

    Ishiko::Error error2;
    error2.fail(error1);

    ISHIKO_FAIL_IF_NOT(error2);
    ISHIKO_FAIL_IF_NEQ(error2.condition().value(), 4);
    ISHIKO_FAIL_IF_NEQ(&error2.condition().category(), &TestErrorCategory1::Get());
    ISHIKO_PASS();
}

void ErrorTests::SucceedTest1(Test& test)
{
    Ishiko::Error error(-1, TestErrorCategory1::Get());
    error.succeed();

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(error.condition().value(), 0);
    ISHIKO_FAIL_IF_NEQ(&error.condition().category(), &Ishiko::SuccessCategory::Get());
    ISHIKO_PASS();
}

void ErrorTests::StreamInsertionTest1(Test& test)
{
    Ishiko::Error error;
    
    std::stringstream errorMessage;
    errorMessage << error;

    ISHIKO_FAIL_IF_NEQ(errorMessage.str(), "Ishiko::SuccessCategory, 0");
    ISHIKO_PASS();
}

void ErrorTests::TryGetMessageTest1(Test& test)
{
    Ishiko::Error error;

    std::string message;
    bool found = error.tryGetMessage(message);

    ISHIKO_FAIL_IF(found);
    ISHIKO_PASS();
}

void ErrorTests::TryGetMessageTest2(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());

    std::string message;
    bool found = error.tryGetMessage(message);

    ISHIKO_FAIL_IF(found);
    ISHIKO_PASS();
}

void ErrorTests::TryGetMessageTest3(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get());

    std::string message;
    bool found = error.tryGetMessage(message);

    ISHIKO_FAIL_IF(found);
    ISHIKO_PASS();
}

void ErrorTests::TryGetMessageTest4(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    std::string message;
    bool found = error.tryGetMessage(message);

    ISHIKO_ABORT_IF_NOT(found);
    ISHIKO_FAIL_IF_NEQ(message, "a bad error");
    ISHIKO_PASS();
}

void ErrorTests::TryGetOriginTest1(Test& test)
{
    Ishiko::Error error;

    const char* file = nullptr;
    int line = -1;
    bool found = error.tryGetOrigin(file, line);

    ISHIKO_FAIL_IF(found);
    ISHIKO_PASS();
}

void ErrorTests::TryGetOriginTest2(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());

    const char* file = nullptr;
    int line = -1;
    bool found = error.tryGetOrigin(file, line);

    ISHIKO_FAIL_IF(found);
    ISHIKO_PASS();
}

void ErrorTests::TryGetOriginTest3(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get());

    const char* file = nullptr;
    int line = -1;
    bool found = error.tryGetOrigin(file, line);

    ISHIKO_FAIL_IF(found);
    ISHIKO_PASS();
}

void ErrorTests::TryGetOriginTest4(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-3, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    const char* file = nullptr;
    int line = -1;
    bool found = error.tryGetOrigin(file, line);

    ISHIKO_ABORT_IF_NOT(found);
    ISHIKO_FAIL_IF_STR_NEQ(file, "file1");
    ISHIKO_FAIL_IF_NEQ(line, 3);
    ISHIKO_PASS();
}

void ErrorTests::ThrowIfTest1(Test& test)
{
    Ishiko::Error error;

    ThrowIf(error);

    ISHIKO_PASS();
}

void ErrorTests::ThrowIfTest2(Test& test)
{
    Ishiko::Error error(-1, TestErrorCategory1::Get());

    try
    {
        ThrowIf(error);

        ISHIKO_FAIL();
    }
    catch (const Ishiko::Exception& e)
    {
        ISHIKO_FAIL_IF_NEQ(e.condition().value(), -1);
        ISHIKO_FAIL_IF_NEQ(&e.condition().category(), &TestErrorCategory1::Get());
        ISHIKO_PASS();
    }
}

void ErrorTests::ThrowIfTest3(Test& test)
{
    Ishiko::Error error(new Ishiko::MessageErrorExtension());
    error.fail(-1, TestErrorCategory1::Get(), "a bad error", "file1", 3);

    try
    {
        ThrowIf(error);

        ISHIKO_FAIL();
    }
    catch (const Ishiko::Exception& e)
    {
        ISHIKO_FAIL_IF_NEQ(e.condition().value(), -1);
        ISHIKO_FAIL_IF_NEQ(&e.condition().category(), &TestErrorCategory1::Get());
        ISHIKO_FAIL_IF_NEQ(e.file(), "file1");
        ISHIKO_FAIL_IF_NEQ(e.line(), 3);
        ISHIKO_PASS();
    }
}
