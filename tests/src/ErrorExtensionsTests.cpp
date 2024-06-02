/*
    Copyright (c) 2022-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorExtensionsTests.hpp"
#include "helpers/TestErrorExtension.hpp"
#include "Ishiko/Errors/Error.hpp"
#include <Ishiko/BasePlatform.hpp>

using namespace Ishiko;

ErrorExtensionsTests::ErrorExtensionsTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Error::Extensions tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("install test 1", InstallTest1);
}

void ErrorExtensionsTests::ConstructorTest1(Test& test)
{
    Error::Extensions extensions;

#ifdef ISHIKO_DEBUG
    ISHIKO_TEST_FAIL_IF_NOT(extensions.dynamic());
#else
    ISHIKO_TEST_FAIL_IF(extensions.dynamic());
#endif
    ISHIKO_TEST_PASS();
}

void ErrorExtensionsTests::InstallTest1(Test& test)
{
    Error::Extensions extensions;

    ErrorCode err = extensions.install<TestErrorExtension>();

    ISHIKO_TEST_FAIL_IF(err);

    const TestErrorExtension* extension;
    bool found = extensions.tryGet(extension);

    ISHIKO_TEST_FAIL_IF_NOT(extension);
    ISHIKO_TEST_PASS();
}
