/*
    Copyright (c) 2019-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorCodeTests.hpp"
#include "helpers/TestErrorCategory1.hpp"
#include "helpers/TestErrorCategory2.hpp"
#include "Ishiko/Errors/ErrorCode.hpp"
#include "Ishiko/Errors/SuccessCategory.hpp"
#include <system_error>

using namespace Ishiko;

ErrorCodeTests::ErrorCodeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "ErrorCode tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("Constructor test 3", ConstructorTest3);
    append<HeapAllocationErrorsTest>("operator==() test 1", EqualityOperatorTest1);
    append<HeapAllocationErrorsTest>("operator==() test 2", EqualityOperatorTest2);
    append<HeapAllocationErrorsTest>("operator!=() test 1", InequalityOperatorTest1);
    append<HeapAllocationErrorsTest>("operator!=() test 2", InequalityOperatorTest2);
    append<HeapAllocationErrorsTest>("fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("fail test 2", FailTest2);
    append<HeapAllocationErrorsTest>("clear test 1", ClearTest1);
    append<HeapAllocationErrorsTest>("operator std::error_code() test 1", StdErrorCodeOperatorTest1);
}

void ErrorCodeTests::ConstructorTest1(Test& test)
{
    ErrorCode error;

    ISHIKO_TEST_FAIL_IF_NEQ(sizeof(error), sizeof(std::error_condition));
    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.value(), 0);
    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::ConstructorTest2(Test& test)
{
    ErrorCode error{SuccessCategory::Get(), 0};

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.value(), 0);
    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::ConstructorTest3(Test& test)
{
    ErrorCode error{TestErrorCategory1::Get(), -1};

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.value(), -1);
    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::EqualityOperatorTest1(Test& test)
{
    ErrorCode error1{TestErrorCategory1::Get(), -1};
    ErrorCode error2{TestErrorCategory1::Get(), -1};

    ISHIKO_TEST_FAIL_IF_NOT(error1 == error2);
    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::EqualityOperatorTest2(Test& test)
{
    ErrorCode error1{TestErrorCategory1::Get(), -1};
    ErrorCode error2{TestErrorCategory1::Get(), -3};

    ISHIKO_TEST_FAIL_IF(error1 == error2);
    
    ErrorCode error3{TestErrorCategory1::Get(), -1};
    ErrorCode error4{TestErrorCategory2::Get(), -1};

    ISHIKO_TEST_FAIL_IF(error3 == error4);

    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::InequalityOperatorTest1(Test& test)
{
    ErrorCode error1{TestErrorCategory1::Get(), -1};
    ErrorCode error2{TestErrorCategory1::Get(), -1};

    ISHIKO_TEST_FAIL_IF(error1 != error2);
    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::InequalityOperatorTest2(Test& test)
{
    ErrorCode error1{TestErrorCategory1::Get(), -1};
    ErrorCode error2{TestErrorCategory1::Get(), -3};

    ISHIKO_TEST_FAIL_IF_NOT(error1 != error2);

    ErrorCode error3{TestErrorCategory1::Get(), -1};
    ErrorCode error4{TestErrorCategory2::Get(), -1};

    ISHIKO_TEST_FAIL_IF_NOT(error3 != error4);

    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::FailTest1(Test& test)
{
    ErrorCode error;
    error.fail(TestErrorCategory1::Get(), -3);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.value(), -3);
    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::FailTest2(Test& test)
{
    ErrorCode error{TestErrorCategory1::Get(), 4};
    error.fail(TestErrorCategory1::Get(), -3);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.value(), -3);
    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::ClearTest1(Test& test)
{
    ErrorCode error{TestErrorCategory1::Get(), -1};
    error.clear();

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.value(), 0);
    ISHIKO_TEST_PASS();
}

void ErrorCodeTests::StdErrorCodeOperatorTest1(Test& test)
{
    ErrorCode error{TestErrorCategory1::Get(), -1};
    std::error_code ec = error;

    ISHIKO_TEST_FAIL_IF_NEQ(ec.value(), -1);
    ISHIKO_TEST_FAIL_IF_NEQ(ec.message(), "generic error");
    ISHIKO_TEST_PASS();
}
