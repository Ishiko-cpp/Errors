/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OROTHER DEALINGS
    IN THE SOFTWARE.
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

void ChainErrorExtension::onFail(int code, const std::string& message, const char* file, int line)
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
