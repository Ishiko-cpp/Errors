/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/Errors/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_IOERROREXTENSION_H_
#define _ISHIKO_ERRORS_IOERROREXTENSION_H_

#include "ErrorExtension.h"
#include "Error.h"
#include <ios>

namespace Ishiko
{

class IOErrorExtension : public ErrorExtension
{
public:
    enum EIOErrorCode
    {
        eError,
        eEOF
    };

    std::ostream& operator<<(std::ostream& os) const override;

    static void Fail(Error& error, EIOErrorCode code, const char* file, int line);
    static void Fail(Error& error, const std::ios& status, const char* file, int line);

    EIOErrorCode code() const;
    
private:
    EIOErrorCode m_code;
    std::string m_file;
    int m_line;
};

}

#endif
