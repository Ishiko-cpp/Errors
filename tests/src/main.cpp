/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorConditionTests.hpp"
#include "ErrorTests.hpp"
#include "MessageErrorExtensionTests.hpp"
#include "IOErrorExtensionTests.hpp"
#include "ChainErrorExtensionTests.hpp"
#include "ExceptionTests.hpp"
#include "StreamUtilitiesTests.hpp"
#include <Ishiko/TestFramework/Core.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoErrors");

    theTestHarness.context().setTestDataDirectory("../../data");

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
