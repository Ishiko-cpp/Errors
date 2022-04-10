/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_EXCEPTIONTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_EXCEPTIONTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class ExceptionTests : public Ishiko::TestSequence
{
public:
    ExceptionTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void ConstructorTest3(Ishiko::Test& test);
    static void ConstructorTest4(Ishiko::Test& test);
    static void ConstructorTest5(Ishiko::Test& test);
};

#endif
