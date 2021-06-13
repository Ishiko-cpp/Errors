/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_CHAINERROREXTENSION_H_
#define _ISHIKO_ERRORS_CHAINERROREXTENSION_H_

#include "ErrorExtension.h"
#include <vector>

namespace Ishiko
{

class ChainErrorExtension : public ErrorExtension
{
public:
    ~ChainErrorExtension() noexcept override;

    void onFail(int code, const std::string& message, const char* file, int line) noexcept override;

    std::ostream& operator<<(std::ostream& os) const override;

private:
    std::vector<std::pair<int, ErrorExtension*>> m_chain;
};

}

#endif
