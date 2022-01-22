/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_STREAMUTILITIESTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_STREAMUTILITIESTESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class StreamUtilitiesTests : public Ishiko::Tests::TestSequence
{
public:
    StreamUtilitiesTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void FailIfCreateFileErrorTest1(Ishiko::Tests::Test& test);
    static void FailIfCreateFileErrorTest2(Ishiko::Tests::Test& test);
    static void FailIfOpenFileErrorTest1(Ishiko::Tests::Test& test);
    static void FailIfOpenFileErrorTest2(Ishiko::Tests::Test& test);
};

#endif
