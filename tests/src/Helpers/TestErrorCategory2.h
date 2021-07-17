/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_TESTS_HELPERS_TESTERRORCATEGORY2_H_
#define _ISHIKO_ERRORS_TESTS_HELPERS_TESTERRORCATEGORY2_H_

#include "Ishiko/Errors/ErrorCategory.h"

class TestErrorCategory2 : public Ishiko::ErrorCategory
{
public:
    static const TestErrorCategory2& Get() noexcept;

    const char* name() const noexcept override;
};

#endif
