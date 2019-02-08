/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "ErrorTests.h"
#include "Ishiko/Errors/Error.h"
#include "Ishiko/Errors/Exception.h"

using namespace Ishiko::TestFramework;

void ErrorTests::AddTests(TestHarness& theTestHarness)
{
    TestSequence& errorTestSequence = theTestHarness.appendTestSequence("Error tests");

    new HeapAllocationErrorsTest("Creation test 1", CreationTest1, errorTestSequence);
    new HeapAllocationErrorsTest("Creation test 2", CreationTest2, errorTestSequence);
    new HeapAllocationErrorsTest("Creation test 3", CreationTest3, errorTestSequence);
    new HeapAllocationErrorsTest("Creation test 4", CreationTest4, errorTestSequence);

    new HeapAllocationErrorsTest("fail test 1", FailTest1, errorTestSequence);
    new HeapAllocationErrorsTest("fail test 2", FailTest2, errorTestSequence);
    new HeapAllocationErrorsTest("fail test 3", FailTest3, errorTestSequence);
    new HeapAllocationErrorsTest("fail test 4", FailTest4, errorTestSequence);

    new HeapAllocationErrorsTest("succeed test 1", SucceedTest1, errorTestSequence);
}

TestResult::EOutcome ErrorTests::CreationTest1()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error;
    if (error && (error.code() == -1))
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ErrorTests::CreationTest2()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error(0);
    if (!error && (error.code() == 0))
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ErrorTests::CreationTest3()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error(-2);
    if (error && (error.code() == -2))
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ErrorTests::CreationTest4()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error(Ishiko::Error::ThrowException);
    if (!error && (error.code() == 0))
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ErrorTests::FailTest1()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error(0);
    error.fail(-3);
    if (error && (error.code() == -3))
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ErrorTests::FailTest2()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error(4);
    error.fail(-3);
    if (error && (error.code() == 4))
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome ErrorTests::FailTest3()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error(Ishiko::Error::ThrowException);
    try
    {
        error.fail(-3);
    }
    catch (const Ishiko::Exception& e)
    {
        if (std::string(e.what()) == "")
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}

TestResult::EOutcome ErrorTests::FailTest4()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error(Ishiko::Error::ThrowException);
    try
    {
        error.fail(-3, "error message", __FILE__, __LINE__);
    }
    catch (const Ishiko::Exception& e)
    {
        if ((std::string(e.what()) == "error message") &&
            (e.file().find("errortests.cpp") != std::string::npos) &&
            (e.line() == (__LINE__ - 6)))
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}

TestResult::EOutcome ErrorTests::SucceedTest1()
{
    TestResult::EOutcome result = TestResult::eFailed;

    Ishiko::Error error;
    error.succeed();
    if (!error && (error.code() == 0))
    {
        result = TestResult::ePassed;
    }

    return result;
}
