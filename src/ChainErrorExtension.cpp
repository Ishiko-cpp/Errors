/*
    Copyright (c) 2019-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#include "ChainErrorExtension.h"
#include "MessageErrorExtension.h"

namespace Ishiko
{

ChainErrorExtension::~ChainErrorExtension()
{
    for (std::pair<int, ErrorExtension*> ext : m_chain)
    {
        ext.second->release();
    }
}

void ChainErrorExtension::onFail(int code, const std::string& message, const char* file, int line) noexcept
{
    m_chain.emplace_back(code, new MessageErrorExtension(message, file, line));
}

std::ostream& ChainErrorExtension::operator<<(std::ostream& os) const
{
    if (m_chain.size() > 0)
    {
        m_chain[0].second->operator<<(os);
    }
    for (size_t i = 1; i < m_chain.size(); ++i)
    {
        os << std::endl << "\tError: " << m_chain[i].first;
        m_chain[i].second->operator<<(os);
    }
    return os;
}

}
