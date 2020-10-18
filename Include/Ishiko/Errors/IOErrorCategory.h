/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_IOERRORCATEGORY_H_
#define _ISHIKO_ERRORS_IOERRORCATEGORY_H_

#include "ErrorCategory.h"

namespace Ishiko
{

class IOErrorCategory : public ErrorCategory
{
public:
    static const IOErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    IOErrorCategory() noexcept = default;
};

}

#endif
