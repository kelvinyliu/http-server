#include "../include/httpRequest.hpp"

httpRequest::httpRequest(const std::string req) {
    size_t headerEnd = req.find("\r\n\r\n");
    if (headerEnd == std::string::npos) {
        std::cout << "Error parsing req header" << std::endl;
        exit(1);
    }

    std::string headers(req.substr(0, headerEnd));
    std::istringstream stream(headers);
    std::string line;
    size_t headerIndex = 1;

    if (!std::getline(stream, line)) {
        std::cout << "Error parsing first line." << std::endl;
        exit(1);
    }

    
    std::istringstream reqLine(line);
    if (!(reqLine >> this->reqMethod >> this->reqPath >> this->reqVersion)) {
        std::cout << "Error extracting request information, potentially malformed request." << std::endl;
        exit(1);
    }

    while (std::getline(stream, line)) {
        size_t colonIndex = line.find(':');
        if (colonIndex == std::string::npos) {
            std::cout << "Error parsing header at line: " << headerIndex << std::endl;
            exit(1);
        }

        std::string key = line.substr(0, colonIndex);
        std::string val = line.substr(colonIndex+1);

        this->reqHeaders[key] = val;
    }

    this->resolveRequestQueries(this->reqPath);

    std::cout << "Request Method:  " << this->reqMethod << std::endl;
    std::cout << "Request Path:    " << this->reqPath << std::endl;
    std::cout << "Request Version: " << this->reqVersion << std::endl;
}

enum RequestMethodType httpRequest::getRequestMethod() const {
    if (this->reqMethod == "GET") {
        return RequestMethodType::GET;
    } else if (this->reqMethod == "POST") {
        return RequestMethodType::POST;
    }
    // others not implemented yet, just error.
    return RequestMethodType::ERROR;
}

const std::string& httpRequest::getRequestPath() const {
    return this->reqPath;
}

void httpRequest::resolveRequestQueries(std::string req) {
    std::map<std::string, std::string> reqQueries;

    size_t queryIndex = req.find('?');
    if (queryIndex == std::string::npos) {
        this->reqQueries = reqQueries;
    };
    std::string filePath = req.substr(0, queryIndex);
    this->reqPath = filePath;

    std::string queries = req.substr(queryIndex+1);

    std::istringstream queryStream(queries);
    std::string kv;
    while (std::getline(queryStream, kv, '&')) {
        size_t equalIndex = kv.find('=');
        if (equalIndex == std::string::npos) {
            // Cannot find equal in kv pair?
            continue;
        }
        std::string key = kv.substr(0, equalIndex);
        std::string val = kv.substr(equalIndex+1);

        reqQueries[key] = val;
    }
    this->reqQueries = reqQueries;
}

const std::map<std::string, std::string> httpRequest::getQueries() const {
    return this->reqQueries;
}

const std::map<std::string, std::string>& httpRequest::getRequestHeaders() const {
    return this->reqHeaders;
}

httpRequest::~httpRequest() {

}