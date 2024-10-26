#pragma once

#include <wtypes.h>
#include <string>

namespace UrlEncoder
{
    bool UrlEncode(const std::string& ansiString, std::string& utf8Result);
    bool UrlDecode(const std::string& utf8string, std::string& ansiResult);

    bool UTF8UrlEncode(const std::string& utf8string, std::string& utf8Result);
    bool UTF8UrlDecode(const std::string& utf8string, std::string& utf8Result);

    bool UTF8StringToAnsiString(const std::string &utf8string, std::string& ansiResult);
    bool AnsiStringToUTF8String(const std::string& ansiString, std::string& utf8result);
};
