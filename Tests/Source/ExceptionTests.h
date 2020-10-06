/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_TESTS_EXCEPTIONTESTS_H_
#define _ISHIKO_ERRORS_TESTS_EXCEPTIONTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class ExceptionTests : public Ishiko::Tests::TestSequence
{
public:
    ExceptionTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
};

#endif
