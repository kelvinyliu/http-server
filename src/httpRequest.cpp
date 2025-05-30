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
        std::string val = line.substr(colonIndex+1, line.size());

        this->reqHeaders[key] = val;
    }

    std::cout << this->reqMethod << std::endl;
    std::cout << this->reqPath << std::endl;
    std::cout << this->reqVersion << std::endl;
}

httpRequest::~httpRequest() {

}