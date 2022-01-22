/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_ERRORCONDITIONTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_ERRORCONDITIONTESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class ErrorConditionTests : public Ishiko::Tests::TestSequence
{
public:
    ErrorConditionTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void ConstructorTest3(Ishiko::Tests::Test& test);
    static void EqualityOperatorTest1(Ishiko::Tests::Test& test);
    static void EqualityOperatorTest2(Ishiko::Tests::Test& test);
    static void InequalityOperatorTest1(Ishiko::Tests::Test& test);
    static void InequalityOperatorTest2(Ishiko::Tests::Test& test);
    static void FailTest1(Ishiko::Tests::Test& test);
    static void FailTest2(Ishiko::Tests::Test& test);
    static void SucceedTest1(Ishiko::Tests::Test& test);
};

#endif
