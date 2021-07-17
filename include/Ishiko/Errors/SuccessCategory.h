/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_SUCCESSCATEGORY_H_
#define _ISHIKO_ERRORS_SUCCESSCATEGORY_H_

#include "ErrorCategory.h"

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
