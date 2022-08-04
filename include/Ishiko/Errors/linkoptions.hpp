/*
    Copyright (c) 2016-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_ERRORS_LINKOPTIONS_HPP
#define GUARD_ISHIKO_CPP_ERRORS_LINKOPTIONS_HPP

#ifdef _DEBUG
#pragma comment(lib, "IshikoErrors-d.lib")
#else
#pragma comment(lib, "IshikoErrors.lib")
#endif

#endif
