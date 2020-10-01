/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_TESTS_CHAINERROREXTENSIONTESTS_H_
#define _ISHIKO_ERRORS_TESTS_CHAINERROREXTENSIONTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class ChainErrorExtensionTests : public Ishiko::Tests::TestSequence
{
public:
    ChainErrorExtensionTests(const Ishiko::Tests::TestNumber& number,
        const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructionTest1(Ishiko::Tests::Test& test);
    static void StreamInsertionTest1(Ishiko::Tests::Test& test);
    static void StreamInsertionTest2(Ishiko::Tests::Test& test);
};

#endif
