/*
    Copyright (c) 2016-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/errors/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_ERRORS_LINKOPTIONS_H_
#define _ISHIKO_ERRORS_LINKOPTIONS_H_

#ifdef _DEBUG
#pragma comment(lib, "IshikoErrors-d.lib")
#else
#pragma comment(lib, "IshikoErrors.lib")
#endif

#endif
