/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_IOERRORCATEGORY_H_
#define _ISHIKO_ERRORS_IOERRORCATEGORY_H_

#include "ErrorCategory.h"
#include "Error.h"

namespace Ishiko
{

class IOErrorCategory : public ErrorCategory
{
public:
    enum EErrorValues
    {
        eGeneric = -1,
        eFileCreationError = -2
    };

    static const IOErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    IOErrorCategory() noexcept = default;
};

void Fail(Error& error, IOErrorCategory::EErrorValues value) noexcept;
void Fail(Error& error, IOErrorCategory::EErrorValues value, const std::string& message, const char* file,
    int line) noexcept;

}

#endif
