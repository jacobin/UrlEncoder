#include "UrlEncoder.h"
#include <iostream>

int main( int argc, char* argv[] )
{
    std::string exclude = "(�й�|�Ї�|���|CN|HK|Hong Kong|HongKong|�㶫|����|����|�Ϻ�|�ƶ�|�V�||�F��|����|�Ϻ�|�Ƅ�|v2cross|V2CROSS)";

    std::string utf8string;
    UrlEncoder::AnsiStringToUTF8String(exclude, utf8string);
    std::string ansiString;
    UrlEncoder::UTF8StringToAnsiString(utf8string, ansiString);
    std::cout << ansiString << std::endl;

    std::string result;
    UrlEncoder::UrlEncode(exclude, result);
    std::string result2;
    UrlEncoder::UrlDecode(result, result2);

    std::cout << result2 << std::endl;;
}