#pragma once

#include <iostream>

#include "storage.h"
#include "tcpserver.h"

class ServerApp {
public:
    ServerApp();
    ~ServerApp();

    void InitServer();
    void Shutdown();

    void InitStorage();
    void InitTcpServer();
    
    void StartMainLoop();

private:
    std::unique_ptr<Storage> storage;
    std::unique_ptr<TcpServer> tcpServer;
    //std::thread ThreadPool;
};

