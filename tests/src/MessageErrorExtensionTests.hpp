/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_MESSAGEERROREXTENSIONTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_MESSAGEERROREXTENSIONTESTS_HPP_

#include <Ishiko/Tests/Core.h>

class MessageErrorExtensionTests : public Ishiko::Tests::TestSequence
{
public:
    MessageErrorExtensionTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ConstructorTest2(Ishiko::Tests::Test& test);
    static void FailTest1(Ishiko::Tests::Test& test);
    static void FailTest2(Ishiko::Tests::Test& test);
    static void StreamInsertionTest1(Ishiko::Tests::Test& test);
};

#endif
