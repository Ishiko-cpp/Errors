/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_TESTS_STREAMUTILITIESTESTS_H_
#define _ISHIKO_ERRORS_TESTS_STREAMUTILITIESTESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class StreamUtilitiesTests : public Ishiko::Tests::TestSequence
{
public:
    StreamUtilitiesTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void FailOnFileCreationErrorTest1(Ishiko::Tests::Test& test);
    static void FailOnFileCreationErrorTest2(Ishiko::Tests::Test& test);
    static void FailOnFileOpeningErrorTest1(Ishiko::Tests::Test& test);
    static void FailOnFileOpeningErrorTest2(Ishiko::Tests::Test& test);
};

#endif
