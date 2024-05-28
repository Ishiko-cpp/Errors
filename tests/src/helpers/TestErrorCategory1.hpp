/*
    Copyright (c) 2019-2024 Xavier Leclercq
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
    const char* message(int ev, char* buffer, size_t len) const noexcept override;
};

#endif
