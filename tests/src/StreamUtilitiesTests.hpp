/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_STREAMUTILITIESTESTS_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_STREAMUTILITIESTESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class StreamUtilitiesTests : public Ishiko::TestSequence
{
public:
    StreamUtilitiesTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void FailIfCreateFileErrorTest1(Ishiko::Test& test);
    static void FailIfCreateFileErrorTest2(Ishiko::Test& test);
    static void FailIfOpenFileErrorTest1(Ishiko::Test& test);
    static void FailIfOpenFileErrorTest2(Ishiko::Test& test);
};

#endif
