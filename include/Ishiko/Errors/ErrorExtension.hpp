/*
    Copyright (c) 2019-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_ERRORS_ERROREXTENSION_HPP_
#define _ISHIKO_CPP_ERRORS_ERROREXTENSION_HPP_

#include <ostream>
#include <string>

namespace Ishiko
{

/// Base class for the error extensions.
class ErrorExtension
{
public:
    /// Destroys the extension.
    /**
        The default implementation calls delete(this).
    */
    virtual void release() noexcept;

    virtual bool tryGetMessage(std::string& message) const noexcept;

    virtual bool tryGetOrigin(const char*& file, int& line) const noexcept;

    virtual void onFail(int code, const std::string& message, const char* file, int line) noexcept;

    virtual std::ostream& operator<<(std::ostream& os) const;

protected:
    virtual ~ErrorExtension() noexcept = default;
};

}

#endif
