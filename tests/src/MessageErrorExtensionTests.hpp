/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_MESSAGEERROREXTENSIONTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_MESSAGEERROREXTENSIONTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class MessageErrorExtensionTests : public Ishiko::TestSequence
{
public:
    MessageErrorExtensionTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void FailTest1(Ishiko::Test& test);
    static void FailTest2(Ishiko::Test& test);
    static void StreamInsertionTest1(Ishiko::Test& test);
};

#endif
