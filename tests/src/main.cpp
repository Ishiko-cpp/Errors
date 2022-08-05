/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ErrorConditionTests.hpp"
#include "ErrorMessageTests.hpp"
#include "ErrorTests.hpp"
#include "MessageErrorExtensionTests.hpp"
#include "ExceptionTests.hpp"
#include <Ishiko/TestFramework/Core.hpp>
#include <exception>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    try
    {
        TestHarness::CommandLineSpecification commandLineSpec;
        commandLineSpec.setDefaultValue("context.data", "../../data");
        commandLineSpec.setDefaultValue("context.output", "../../output");
        commandLineSpec.setDefaultValue("context.reference", "../../reference");

        Configuration configuration = commandLineSpec.createDefaultConfiguration();
        CommandLineParser::parse(commandLineSpec, argc, argv, configuration);

        TestHarness theTestHarness("Ishiko/C++ Errors Library Tests", configuration);

        TestSequence& theTests = theTestHarness.tests();
        theTests.append<ErrorConditionTests>();
        theTests.append<ErrorMessageTests>();
        theTests.append<ErrorTests>();
        theTests.append<MessageErrorExtensionTests>();
        theTests.append<ExceptionTests>();

        return theTestHarness.run();
    }
    catch (const std::exception& e)
    {
        return TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return TestApplicationReturnCode::exception;
    }
}
