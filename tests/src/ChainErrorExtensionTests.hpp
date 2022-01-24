/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_CHAINERROREXTENSIONTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_CHAINERROREXTENSIONTESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class ChainErrorExtensionTests : public Ishiko::Tests::TestSequence
{
public:
    ChainErrorExtensionTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void ConstructionTest1(Ishiko::Tests::Test& test);
    static void StreamInsertionTest1(Ishiko::Tests::Test& test);
    static void StreamInsertionTest2(Ishiko::Tests::Test& test);
};

#endif
