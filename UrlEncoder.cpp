////////////////////////////////////////////////////////////////////////////////
#include "UrlEncoder.h"
#include <string>
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////
// https://github.com/tindy2013/subconverter////////////////////////////////////
static unsigned char toHex(unsigned char x)
{
    return  x > 9 ? x + 55 : x + 48;
}

////////////////////////////////////////////////////////////////////////////////
// https://github.com/tindy2013/subconverter////////////////////////////////////
static unsigned char fromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z')
        y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z')
        y = x - 'a' + 10;
    else if (x >= '0' && x <= '9')
        y = x - '0';
    else
        y = x;
    return y;
}

////////////////////////////////////////////////////////////////////////////////
// https://github.com/tindy2013/subconverter////////////////////////////////////
static std::string urlEncode(const std::string& utf8str)
{
    std::string strTemp = "";
    size_t length = utf8str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (isalnum((unsigned char)utf8str[i]) ||
            (utf8str[i] == '-') ||
            (utf8str[i] == '_') ||
            (utf8str[i] == '.') ||
            (utf8str[i] == '~'))
            strTemp += utf8str[i];
        else
        {
            strTemp += '%';
            strTemp += toHex((unsigned char)utf8str[i] >> 4);
            strTemp += toHex((unsigned char)utf8str[i] % 16);
        }
    }
    return strTemp;
}

////////////////////////////////////////////////////////////////////////////////
// https://github.com/tindy2013/subconverter////////////////////////////////////
static std::string urlDecode(const std::string& utf8str)
{
    std::string strTemp;
    size_t length = utf8str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (utf8str[i] == '+')
            strTemp += ' ';
        else if (utf8str[i] == '%')
        {
            if (i + 2 >= length)
                return strTemp;
            if (isalnum(utf8str[i + 1]) && isalnum(utf8str[i + 2]))
            {
                unsigned char high = fromHex((unsigned char)utf8str[++i]);
                unsigned char low = fromHex((unsigned char)utf8str[++i]);
                strTemp += high * 16 + low;
            }
            else
                strTemp += utf8str[i];
        }
        else
            strTemp += utf8str[i];
    }
    return strTemp;
}

////////////////////////////////////////////////////////////////////////////////
namespace UrlEncoder
{
    ////////////////////////////////////////////////////////////////////////
    bool UTF8StringToAnsiString(const std::string& utf8string, std::string& ansiResult)
    {
        int nUtf8Len = utf8string.length();
        wchar_t* wbuffer = new(std::nothrow) wchar_t[nUtf8Len + 1];
        if (NULL == wbuffer) return false;
        int nActualLen = MultiByteToWideChar(CP_UTF8, MB_PRECOMPOSED, utf8string.c_str(), nUtf8Len, wbuffer, nUtf8Len + 1);
        if (0 == nActualLen) return false;
        wbuffer[nActualLen] = NULL;
        int nRequiredSize = WideCharToMultiByte(CP_ACP, 0, wbuffer, -1, NULL, 0, NULL, NULL);
        if (0 == nRequiredSize) return false;
        char* buffer = new(std::nothrow) char[nRequiredSize];
        if (NULL == buffer) return false;
        if (0 == WideCharToMultiByte(CP_ACP, 0, wbuffer, -1, buffer, nRequiredSize, NULL, NULL)) return false;
        ansiResult = buffer;
        return true;
    }

    ////////////////////////////////////////////////////////////////////////
    bool AnsiStringToUTF8String(const std::string& ansiString, std::string& utf8result)
    {
        int nAnsiLen = ansiString.length();
        wchar_t* wbuffer = new(std::nothrow) wchar_t[nAnsiLen + 1];
        if (NULL == wbuffer) return false;
        int nActualLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, ansiString.c_str(), nAnsiLen, wbuffer, nAnsiLen + 1);
        if (0 == nActualLen) return false;
        wbuffer[nActualLen] = NULL;
        int nRequiredSize = WideCharToMultiByte(CP_UTF8, 0, wbuffer, -1, NULL, 0, NULL, NULL);
        if (0 == nRequiredSize) return false;
        char* buffer = new(std::nothrow) char[nRequiredSize];
        if (NULL == buffer) return false;
        if (0 == WideCharToMultiByte(CP_UTF8, 0, wbuffer, -1, buffer, nRequiredSize, NULL, NULL)) return false;
        utf8result = buffer;
        return true;
    }

    ////////////////////////////////////////////////////////////////////////
    bool UrlEncode(const std::string& ansiString, std::string& utf8Result)
    {
        std::string utf8Result2;
        if (!AnsiStringToUTF8String(ansiString, utf8Result2)) return false;
        utf8Result = urlEncode(utf8Result2);
        return true;
    }

    ////////////////////////////////////////////////////////////////////////
    bool UrlDecode(const std::string& utf8string, std::string& ansiResult)
    {
        std::string utf8string2 = urlDecode(utf8string);
        std::string ansiResult2;
        if (!UTF8StringToAnsiString(utf8string2, ansiResult2)) return false;
        ansiResult = ansiResult2;
        return true;
    }

    ////////////////////////////////////////////////////////////////////////
    bool UTF8UrlEncode(const std::string& utf8string, std::string& utf8Result)
    {
        utf8Result = urlEncode(utf8string);
        return true;
    }

    ////////////////////////////////////////////////////////////////////////
    bool UTF8UrlDecode(const std::string& utf8string, std::string& utf8Result)
    {
        utf8Result = urlDecode(utf8string);
        return true;
    }
}

////////////////////////////////// END /////////////////////////////////////////
