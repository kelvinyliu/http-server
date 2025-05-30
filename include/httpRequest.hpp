#pragma once
#include <string_view>
#include <string>
#include <iostream>
#include <sstream>
#include <map>

enum RequestMethodType {
    GET,
    POST,
    ERROR,
};

class httpRequest
{
private:
    std::string reqMethod, reqPath, reqVersion;
    std::map<std::string, std::string> reqHeaders;
public:
    httpRequest(const std::string req);
    const std::string&      getRequestPath();
    enum RequestMethodType getRequestMethod();
    ~httpRequest();
};

