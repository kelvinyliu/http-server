#pragma once
#include <string_view>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

class httpRequest
{
private:
    std::string reqMethod, reqPath, reqVersion;
    std::map<std::string, std::string> reqHeaders;
public:
    httpRequest(const std::string req);
    ~httpRequest();
};
