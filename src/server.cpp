#include "../include/server.hpp"
#include "../include/httpRequest.hpp"

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
    struct sockaddr_in clientAddr;
    socklen_t clientSockLen = sizeof(clientAddr);
    int clientSocket = accept(this->serverSocket, (sockaddr *)&clientAddr, &clientSockLen);

    char clientIp[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIp, INET_ADDRSTRLEN);
    std::cout << "----- Received data from: \n" << clientIp << std::endl;

    // const char* msg = "Hello, world!";
    // int len = strlen(msg);
    // int bytesSent = 0;
    // bytesSent = send(clientSocket, msg, len, 0);

    char receivedText[MAX_RECV_BUFFER_SIZE];

    ssize_t recvBytes = recv(clientSocket, receivedText, MAX_RECV_BUFFER_SIZE-1, 0);
    if (recvBytes == -1) {
        std::cout << "Error receiving data from client" << std::endl;
        exit(1);
    }

    this->parseHTTPRequest(receivedText);

    std::cout << strlen(receivedText) << std::endl;
    
}

void server::parseHTTPRequest(char* receivedText) {
    std::string recv(receivedText);
    httpRequest req(recv);
}