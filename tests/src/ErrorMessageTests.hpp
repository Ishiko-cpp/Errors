/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_TESTS_ERRORMESSAGETESTS_HPP_
#define GUARD_ISHIKO_CPP_ERRORS_TESTS_ERRORMESSAGETESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class ErrorMessageTests : public Ishiko::TestSequence
{
public:
    ErrorMessageTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
