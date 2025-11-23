#pragma once

#include <vector>
#include <string>
#include <memory>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "msgHandler.h"

struct Client {
    int client_sock;

};

class TcpServer {
public:
    TcpServer(const std::string& addr, int port);
    TcpServer();

    void InitServer();
    void Shutdown();

    int StartAccept();
    
private:
    int InitSocket();
    int ClientProc(int cl_fd);

    std::string address;
    sockaddr_in s_addr;
    int port;
    int sock;
    std::vector<char> buffer;
    std::unique_ptr<MsgHandler> handler;
};