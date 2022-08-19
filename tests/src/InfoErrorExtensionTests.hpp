/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_TESTS_INFOERROREXTENSIONTESTS_HPP
#define GUARD_ISHIKO_CPP_ERRORS_TESTS_INFOERROREXTENSIONTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class InfoErrorExtensionTests : public Ishiko::TestSequence
{
public:
    InfoErrorExtensionTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ConstructorTest2(Ishiko::Test& test);
    static void ConstructorTest3(Ishiko::Test& test);
    static void FailTest1(Ishiko::Test& test);
    static void FailTest2(Ishiko::Test& test);
    static void StreamInsertionTest1(Ishiko::Test& test);
};

#endif
