/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_ERRORTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_ERRORTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class ErrorTests : public Ishiko::TestSequence
{
public:
    ErrorTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void EqualityOperatorTest1(Ishiko::Test& test);
    static void EqualityOperatorTest2(Ishiko::Test& test);
    static void InequalityOperatorTest1(Ishiko::Test& test);
    static void InequalityOperatorTest2(Ishiko::Test& test);
    static void FailTest1(Ishiko::Test& test);
    static void FailTest2(Ishiko::Test& test);
    static void FailTest3(Ishiko::Test& test);
    static void SucceedTest1(Ishiko::Test& test);
    static void StreamInsertionTest1(Ishiko::Test& test);
    static void TryGetMessageTest1(Ishiko::Test& test);
    static void TryGetMessageTest2(Ishiko::Test& test);
    static void TryGetMessageTest3(Ishiko::Test& test);
    static void TryGetMessageTest4(Ishiko::Test& test);
    static void TryGetOriginTest1(Ishiko::Test& test);
    static void TryGetOriginTest2(Ishiko::Test& test);
    static void TryGetOriginTest3(Ishiko::Test& test);
    static void TryGetOriginTest4(Ishiko::Test& test);
    static void ThrowIfTest1(Ishiko::Test& test);
    static void ThrowIfTest2(Ishiko::Test& test);
    static void ThrowIfTest3(Ishiko::Test& test);
};

#endif
