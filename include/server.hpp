#pragma once
#include <cstdint>
#include <netdb.h>
#include <cstddef>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

class server
{
private:
    const int backlog = 5;
    int serverSocket;
    struct addrinfo hints;
    struct addrinfo *serverInformation;

public:
    server(const uint16_t PORT);
    void initSocket();
    void startAccepting();
    ~server();
};
