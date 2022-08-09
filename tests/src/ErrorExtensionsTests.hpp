/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_TESTS_ERROREXTENSIONSTESTS_HPP
#define GUARD_ISHIKO_CPP_ERRORS_TESTS_ERROREXTENSIONSTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class ErrorExtensionsTests : public Ishiko::TestSequence
{
public:
    ErrorExtensionsTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
};

#endif
