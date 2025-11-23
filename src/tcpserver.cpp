#include "tcpserver.h"

#include <iostream>

#include <strings.h>

TcpServer::TcpServer(const std::string& addr, int _port) {
    address = addr;
    port = _port;
    buffer.reserve(1024);
}

TcpServer::TcpServer() {

}

void TcpServer::InitServer() {
    std::cout << "INFO: TcpServer init\n";

    handler = std::make_unique<MsgHandler>();

    if(InitSocket()) {
        std::cout << "ERROR: TcpServer init failed\n";
    }
}

void TcpServer::Shutdown() {

}

int TcpServer::InitSocket() {
    std::cout << "INFO: TcpServer socket init\n";
    int res;
    int trueval = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        std::cout << "ERROR: Failed to init socket\n";
        return -1;
    }
    
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    s_addr.sin_port = htons(port);

    res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &trueval, sizeof(int));
    if (res == -1) {
        std::cout << "ERROR: Failedto setsockopt\n";
        return -1;
    }
    
    res = bind(sock, (sockaddr*)&s_addr, sizeof(s_addr));
    if(res == -1) {
        std::cout << "ERROR: Failed to bind socket\n";
        return res;
    }

    res = listen(sock, 10);
    if(res == -1) {
        std::cout << "ERROR: Failed to listen socket\n";
        return res;
    }

    return 0;
}

int TcpServer::StartAccept() {
    int res;
    sockaddr_in cl_addr;
    unsigned int len = sizeof(cl_addr);

    while (1) {        
        int cl_fd = accept(sock, (sockaddr*)&cl_addr, &len);
        if(cl_fd == -1) {
            std::cout << "ERROR: Failed to accept client\n";
            return -1;
        }
        
        res = ClientProc(cl_fd);
        if(res == -1) {
            std::cout << "ERROR: Client proc returned error\n";
            return -1;
        }
    }
}

int TcpServer::ClientProc(int cl_fd) {
    int bytes_read;
    std::string responce;
    while(1) {
        bzero(buffer.data(), 1024);

        bytes_read = recv(cl_fd, buffer.data(), 1024, 0);
        if(bytes_read > 0) {
            std::string msg = std::string(buffer.data(), bytes_read);
            std::cout << "Recv: " << msg << "\n";
            handler->ParseMessage(msg);
            responce = msg;
        }
        else if(bytes_read < 0) {
            std::cout << "ERROR: Read from socket failed\n";
            return -1;
        } else {
            std::cout << "Recv: Client closed\n";
            close(cl_fd);
            return 0;
        }

        send(cl_fd, responce.c_str(), responce.size(), 0);

    }
    return 0;
}