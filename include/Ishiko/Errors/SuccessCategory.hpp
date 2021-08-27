/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_SUCCESSCATEGORY_HPP_
#define _ISHIKO_CPP_ERRORS_SUCCESSCATEGORY_HPP_

#include "ErrorCategory.hpp"

namespace Ishiko
{

class SuccessCategory : public ErrorCategory
{
public:
    static const SuccessCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    SuccessCategory() noexcept = default;
};

}

#endif
