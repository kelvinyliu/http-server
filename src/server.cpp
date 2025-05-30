#include "../include/server.hpp"
#include "../include/server_helper.hpp"
#include "../include/httpRequest.hpp"
#include <fstream>

server::server(const uint16_t PORT) {
    memset(&this->hints, 0, sizeof(this->hints));
    this->hints.ai_family = AF_UNSPEC;
    this->hints.ai_socktype = SOCK_STREAM; // TCP
    this->hints.ai_flags = AI_PASSIVE;

    std::string portString = std::to_string(PORT);
    // set the port to the param
    int status = getaddrinfo(NULL, portString.c_str(), &this->hints, &this->serverInformation);
    if (status != 0) {
        std::cout << "addrinfo init fail." << std::endl;
        exit(1);
    }
}

server::~server() {
    close(this->serverSocket);
    freeaddrinfo(this->serverInformation);
}

void server::initSocket() {
    int _sock = socket(this->serverInformation->ai_family, this->serverInformation->ai_socktype, this->serverInformation->ai_protocol);
    if (_sock == -1) {
        std::cout << "sock init failed." << std::endl;
        exit(1);
    }

    int opt = 1;
    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cout << "Error in reusing." << std::endl;
        this->~server();
        exit(1);
    }

    this->serverSocket = _sock;
    int status = bind(this->serverSocket, this->serverInformation->ai_addr, this->serverInformation->ai_addrlen);
    if (status != 0) {
        std::cout << "sock bind fail." << std::endl;
        exit(1);
    }

    listen(this->serverSocket, this->BACKLOG);
}

void server::startAccepting() {
    // temp like this for now:
    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientSockLen = sizeof(clientAddr);
        int clientSocket = accept(this->serverSocket, (sockaddr *)&clientAddr, &clientSockLen);

        char clientIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, INET_ADDRSTRLEN);
        std::cout << "----- Received data from: " << clientIp << std::endl;

        char receivedText[MAX_RECV_BUFFER_SIZE];

        ssize_t recvBytes = recv(clientSocket, receivedText, MAX_RECV_BUFFER_SIZE-1, 0);
        if (recvBytes == -1) {
            std::cout << "Error receiving data from client" << std::endl;
            exit(1);
        }

        this->parseHTTPRequest(receivedText, clientSocket);
        // once parsing request is finished, finish up the socket.
        close(clientSocket);

        std::cout << strlen(receivedText) << std::endl;
    }
    
}

void server::serve404Page(int reqSocket) {
    std::string notFound =
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/html\r\n"
        "Content-Length: 13\r\n"
        "\r\n"
        "404 Not Found";

    send(reqSocket, notFound.c_str(), notFound.size(), 0);
}

void server::parseHTTPRequest(char* receivedText, int reqSocket) {
    std::string recv(receivedText);
    httpRequest req(recv);

    enum RequestMethodType reqMethod = req.getRequestMethod();
    std::string reqPath = req.getRequestPath();
    const std::map<std::string, std::string>& reqHeaders = req.getRequestHeaders();

    /*
        Handle serving server files,
        the default '/' get should point to index.html in the base folder.

        the base folder should be "htdocs", so any request path should be from that folder.

        get method -> 
        call serving method, pass reqpath -> 
        check for existence of path ->
        respond appropriately with correct headers and html content
    */

    if (reqHeaders.find("Host") == reqHeaders.end()) {
        this->serve404Page(reqSocket);
        return;
    }

    if (reqMethod == RequestMethodType::GET) {
        this->serveGetRequest(req, reqSocket);
    }
}

void server::serveGetRequest(const httpRequest& req, int reqSocket) {
    std::string filePath = "htdocs/";
    const std::string reqPath = req.getRequestPath();

    // serve correct file, '/' is going to refer to index.html
    if (reqPath == "/") {
        filePath.append("index.html");
    } else {
        filePath.append(reqPath);
    }

    std::map<std::string, std::string> queries = req.getQueries();

    std::ifstream requestedFile(filePath, std::ios::binary);
    if (!requestedFile.is_open()) {
        // return an error page, for now just exit program and error
        std::cout << filePath << std::endl;
        this->serve404Page(reqSocket);
        return;
    }
    std::ostringstream bodyStream;
    bodyStream << requestedFile.rdbuf();
    std::string body = bodyStream.str();

    std::ostringstream responseStream;
    responseStream << "HTTP/1.1 200 OK" << "\r\n";
    responseStream << "Content-Length: " << body.size() << "\r\n";
    responseStream << "Content-Type: " << getMIMEType(filePath) << "\r\n";
    responseStream << "Connection: close" << "\r\n";
    responseStream << "\r\n";
    responseStream << body;

    std::string response = responseStream.str();
    send(reqSocket, response.c_str(), response.size(), 0);
}

