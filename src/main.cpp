#include "../include/server.hpp"
#include <iostream>

int main()
{
    server s(8080);
    s.initSocket();
    s.startAccepting();
    
    return 0;
}