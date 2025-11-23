#include <iostream>

#include "src/server.h"

int main() {
    ServerApp serv;
    
    serv.InitServer();
    serv.StartMainLoop();
    serv.Shutdown();

    return 0;
}