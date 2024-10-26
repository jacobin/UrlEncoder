#include "UrlEncoder.h"
#include <iostream>

int main( int argc, char* argv[] )
{
    std::string exclude = "(中国|中國|香港|CN|HK|Hong Kong|HongKong|广东|贵州|北京|上海|移动|廣東|貴州|北京|上海|移動|v2cross|V2CROSS)";

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