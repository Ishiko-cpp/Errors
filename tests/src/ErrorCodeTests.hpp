/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_TESTS_ERRORCODETESTS_HPP
#define GUARD_ISHIKO_CPP_ERRORS_TESTS_ERRORCODETESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class ErrorCodeTests : public Ishiko::TestSequence
{
public:
    ErrorCodeTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void ConstructorTest3(Ishiko::Test& test);
    static void EqualityOperatorTest1(Ishiko::Test& test);
    static void EqualityOperatorTest2(Ishiko::Test& test);
    static void InequalityOperatorTest1(Ishiko::Test& test);
    static void InequalityOperatorTest2(Ishiko::Test& test);
    static void FailTest1(Ishiko::Test& test);
    static void FailTest2(Ishiko::Test& test);
    static void ClearTest1(Ishiko::Test& test);
    static void StdErrorCodeOperatorTest1(Ishiko::Test& test);
};

#endif
