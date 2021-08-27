/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_CHAINERROREXTENSION_HPP_
#define _ISHIKO_CPP_ERRORS_CHAINERROREXTENSION_HPP_

#include "ErrorExtension.hpp"
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
