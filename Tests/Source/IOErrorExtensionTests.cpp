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

#include "IOErrorExtensionTests.h"
#include "Ishiko/Errors/IOErrorExtension.h"
#include "Ishiko/Errors/Error.h"
#include <errno.h>

using namespace Ishiko::Tests;

IOErrorExtensionTests::IOErrorExtensionTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "IOErrorExtension tests", environment)
{
    append<HeapAllocationErrorsTest>("Construction test 1", ConstructionTest1);
    append<HeapAllocationErrorsTest>("Fail test 1", FailTest1);
    append<HeapAllocationErrorsTest>("Fail test 2", FailTest2);
}

void IOErrorExtensionTests::ConstructionTest1(Test& test)
{
    Ishiko::IOErrorExtension ioExtension;

    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest1(Test& test)
{
    Ishiko::Error error;
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF);

    ISHTF_FAIL_IF(error.extension());
    ISHTF_PASS();
}

void IOErrorExtensionTests::FailTest2(Test& test)
{
    Ishiko::Error error(0, new Ishiko::IOErrorExtension());
    Ishiko::IOErrorExtension::Fail(error, Ishiko::IOErrorExtension::eEOF);

    ISHTF_FAIL_UNLESS(error.code() == EIO);

    Ishiko::IOErrorExtension* ext = dynamic_cast<Ishiko::IOErrorExtension*>(error.extension());

    ISHTF_ABORT_UNLESS(ext);
    ISHTF_FAIL_UNLESS(ext->code() == Ishiko::IOErrorExtension::eEOF);
    ISHTF_PASS();
}
