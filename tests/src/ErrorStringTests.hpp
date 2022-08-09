/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_TESTS_ERRORSTRINGTESTS_HPP
#define GUARD_ISHIKO_CPP_ERRORS_TESTS_ERRORSTRINGTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class ErrorStringTests : public Ishiko::TestSequence
{
public:
    ErrorStringTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
