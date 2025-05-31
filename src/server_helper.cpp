#include "../include/server_helper.hpp"
#include <ctime>
#include <sstream>

std::string getMIMEType(const std::string& fileName) {
    if (fileName.size() >= 5 && fileName.substr(fileName.size() - 5) == ".html") return "text/html";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".css") return "text/css";
    if (fileName.size() >= 3 && fileName.substr(fileName.size() - 3) == ".js") return "application/javascript";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".png") return "image/png";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".jpg") return "image/jpeg";
    if (fileName.size() >= 5 && fileName.substr(fileName.size() - 5) == ".jpeg") return "image/jpeg";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".gif") return "image/gif";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".svg") return "image/svg+xml";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".ico") return "image/x-icon";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".txt") return "text/plain";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".xml") return "application/xml";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".json") return "application/json";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".pdf") return "application/pdf";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".zip") return "application/zip";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".mp3") return "audio/mpeg";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".mp4") return "video/mp4";
    if (fileName.size() >= 5 && fileName.substr(fileName.size() - 5) == ".webm") return "video/webm";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".ogg") return "audio/ogg";
    if (fileName.size() >= 5 && fileName.substr(fileName.size() - 5) == ".opus") return "audio/opus";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".wav") return "audio/wav";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".bmp") return "image/bmp";
    if (fileName.size() >= 4 && fileName.substr(fileName.size() - 4) == ".webp") return "image/webp";
    return "application/octet-stream"; // default MIME type
}

std::string generateCurrentDateTime() {
    time_t now = std::time(NULL);
    char dtNow[100];
    std::strftime(dtNow, sizeof(dtNow), "%a, %d %b %Y %H:%M:%S GMT", std::gmtime(&now));

    return dtNow;
}