/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_TESTS_HELPERS_TESTERRORCATEGORY1_HPP
#define GUARD_ISHIKO_CPP_ERRORS_TESTS_HELPERS_TESTERRORCATEGORY1_HPP

#include "Ishiko/Errors/ErrorCategory.hpp"

class TestErrorCategory1 : public Ishiko::ErrorCategory
{
public:
    static const TestErrorCategory1& Get() noexcept;

    const char* name() const noexcept override;
    std::ostream& streamOut(int value, std::ostream& os) const override;
};

#endif
