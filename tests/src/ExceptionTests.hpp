/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_EXCEPTIONTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_EXCEPTIONTESTS_HPP_

#include <Ishiko/Tests/Core.h>

class ExceptionTests : public Ishiko::Tests::TestSequence
{
public:
    ExceptionTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void ConstructorTest3(Ishiko::Tests::Test& test);
    static void ConstructorTest4(Ishiko::Tests::Test& test);
    static void ConstructorTest5(Ishiko::Tests::Test& test);
};

#endif
