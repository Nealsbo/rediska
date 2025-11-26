#pragma once

#include <vector>
#include <queue>
#include <string>
#include <memory>

#include <thread>
#include <mutex>
#include <condition_variable>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "msgHandler.h"
#include "threadPool.h"

enum class e_ClientState {
    IDLE = 0,
    READ = 1,
    SEND = 2,
    CLOSE = 3
};

struct ClientData {
    int cl_fd;
    std::vector<char> recvbuf;
    std::vector<char> sendbuf;
    // To use
    int ttl;
    e_ClientState state;

    void HandleRead();
    void HandleWrite();
};

void ConnectionHandler(int cl_fd);
void fd_set_nb(int sock);

class TcpServer {
public:
    TcpServer(const std::string& addr, int port);
    TcpServer();

    void InitServer();
    void Shutdown();

    int StartAccept();
    
private:
    int InitSocket();
    int SpawnThreads(int num_threads);
    int StopThreads();
    int ClientProc(int cl_fd);

    std::string address;
    sockaddr_in s_addr;
    int port;
    int sock;
    int workers_count;
    std::vector<char> buffer;
    std::vector<ClientData> clients;
    std::unique_ptr<MsgHandler> handler;

    // Move to other place?
    ThreadPool thread_pool;
};