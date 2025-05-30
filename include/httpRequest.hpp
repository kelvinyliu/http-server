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
    std::map<std::string, std::string> reqQueries;

    void resolveRequestQueries(std::string req);

public:
    httpRequest(const std::string req);
    const std::string&  getRequestPath() const;
    enum RequestMethodType  getRequestMethod() const;
    const std::map<std::string, std::string> getQueries() const;
    ~httpRequest();
};

