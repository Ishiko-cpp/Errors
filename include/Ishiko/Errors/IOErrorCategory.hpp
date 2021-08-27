/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_IOERRORCATEGORY_HPP_
#define _ISHIKO_CPP_ERRORS_IOERRORCATEGORY_HPP_

#include "ErrorCategory.hpp"
#include "Error.hpp"

namespace Ishiko
{

class IOErrorCategory : public ErrorCategory
{
public:
    enum EErrorValues
    {
        eGenericError = -1,
        eCreateFileError = -2,
        eOpenFileError = -3
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
