#pragma once
#include <cstdint>
#include <netdb.h>
#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sstream>
#include <vector>

class server
{
private:
    const int BACKLOG = 5;
    const int MAX_RECV_BUFFER_SIZE = 4096;

    int serverSocket;
    struct addrinfo hints;
    struct addrinfo *serverInformation;

    void parseHTTPRequest(char* recvText);

public:
    server(const uint16_t PORT);
    void initSocket();
    void startAccepting();
    ~server();
};
