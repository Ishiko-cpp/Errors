/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_IOERROREXTENSIONTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_IOERROREXTENSIONTESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class IOErrorExtensionTests : public Ishiko::Tests::TestSequence
{
public:
    IOErrorExtensionTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void ConstructionTest1(Ishiko::Tests::Test& test);
    static void FailTest1(Ishiko::Tests::Test& test);
    static void FailTest2(Ishiko::Tests::Test& test);
    static void FailTest3(Ishiko::Tests::Test& test);
    static void FailTest4(Ishiko::Tests::Test& test);
    static void FailTest5(Ishiko::Tests::Test& test);
    static void FailTest6(Ishiko::Tests::Test& test);
    static void StreamInsertionTest1(Ishiko::Tests::Test& test);
};

#endif
