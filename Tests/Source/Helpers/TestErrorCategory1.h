/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_TESTS_HELPERS_TESTERRORCATEGORY1_H_
#define _ISHIKO_ERRORS_TESTS_HELPERS_TESTERRORCATEGORY1_H_

#include "Ishiko/Errors/ErrorCategory.h"

class TestErrorCategory1 : public Ishiko::ErrorCategory
{
public:
    static const TestErrorCategory1& Get() noexcept;
};

#endif
