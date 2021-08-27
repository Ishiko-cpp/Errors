/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_TESTS_HELPERS_TESTERRORCATEGORY1_HPP_
#define _ISHIKO_CPP_ERRORS_TESTS_HELPERS_TESTERRORCATEGORY1_HPP_

#include "Ishiko/Errors/ErrorCategory.hpp"

class TestErrorCategory1 : public Ishiko::ErrorCategory
{
public:
    static const TestErrorCategory1& Get() noexcept;

    const char* name() const noexcept override;
};

#endif
