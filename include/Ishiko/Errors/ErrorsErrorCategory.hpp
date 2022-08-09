/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_ERRORSERRORCATEGORY_HPP
#define GUARD_ISHIKO_CPP_ERRORS_ERRORSERRORCATEGORY_HPP

#include "ErrorCategory.hpp"
#include <ostream>

namespace Ishiko
{

class ErrorsErrorCategory : public ErrorCategory
{
public:
    struct Value
    {
        enum
        {
            generic = -1,
            memory_allocation_failure = -2
        };
    };

    static const ErrorsErrorCategory& Get() noexcept;

    const char* name() const noexcept override;
    std::ostream& streamOut(int value, std::ostream& os) const override;

private:
    ErrorsErrorCategory() noexcept = default;
};

}

#endif
