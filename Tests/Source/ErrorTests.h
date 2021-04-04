/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_TESTS_ERRORTESTS_H_
#define _ISHIKO_ERRORS_TESTS_ERRORTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class ErrorTests : public Ishiko::Tests::TestSequence
{
public:
    ErrorTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void FailTest1(Ishiko::Tests::Test& test);
    static void FailTest2(Ishiko::Tests::Test& test);
    static void SucceedTest1(Ishiko::Tests::Test& test);
    static void StreamInsertionTest1(Ishiko::Tests::Test& test);
    static void TryGetMessageTest1(Ishiko::Tests::Test& test);
    static void TryGetMessageTest2(Ishiko::Tests::Test& test);
    static void TryGetMessageTest3(Ishiko::Tests::Test& test);
    static void TryGetMessageTest4(Ishiko::Tests::Test& test);
    static void TryGetOriginTest1(Ishiko::Tests::Test& test);
    static void TryGetOriginTest2(Ishiko::Tests::Test& test);
    static void TryGetOriginTest3(Ishiko::Tests::Test& test);
    static void TryGetOriginTest4(Ishiko::Tests::Test& test);
    static void ThrowIfTest1(Ishiko::Tests::Test& test);
    static void ThrowIfTest2(Ishiko::Tests::Test& test);
    static void ThrowIfTest3(Ishiko::Tests::Test& test);
};

#endif
