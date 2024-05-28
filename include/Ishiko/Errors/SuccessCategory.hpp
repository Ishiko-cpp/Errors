/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_SUCCESSCATEGORY_HPP
#define GUARD_ISHIKO_CPP_ERRORS_SUCCESSCATEGORY_HPP

#include "ErrorCategory.hpp"

namespace Ishiko
{

class SuccessCategory : public ErrorCategory
{
public:
    static const SuccessCategory& Get() noexcept;

    const char* name() const noexcept override;
    const char* message(int ev, char* buffer, size_t len) const noexcept override;

private:
    SuccessCategory() noexcept = default;
};

}

#endif
