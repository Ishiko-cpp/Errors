/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorConditionTests.h"
#include "ErrorTests.h"
#include "MessageErrorExtensionTests.h"
#include "IOErrorExtensionTests.h"
#include "ChainErrorExtensionTests.h"
#include "ExceptionTests.h"
#include "StreamUtilitiesTests.h"
#include <Ishiko/Tests/Core.h>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoErrors");

    theTestHarness.environment().setTestDataDirectory("../../TestData");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<ErrorConditionTests>();
    theTests.append<ErrorTests>();
    theTests.append<MessageErrorExtensionTests>();
    theTests.append<IOErrorExtensionTests>();
    theTests.append<ChainErrorExtensionTests>();
    theTests.append<ExceptionTests>();
    theTests.append<StreamUtilitiesTests>();

    return theTestHarness.run();
}
