#include "server.h"

ServerApp::ServerApp() {

}
ServerApp::~ServerApp() {

}

void ServerApp::InitServer() {
    std::cout << "INFO: ServerApp init\n";
    InitStorage();
    InitTcpServer();
}

void ServerApp::Shutdown() {
    std::cout << "INFO: ServerApp shutdown\n";
    tcpServer->Shutdown();
    storage->Shutdown();
}

void ServerApp::InitStorage() {
    std::cout << "INFO: ServerApp init storage\n";
    storage = std::make_unique<Storage>();
    storage->Init();
}

void ServerApp::InitTcpServer() {
    std::cout << "INFO: ServerApp init TcpServer\n";
    tcpServer = std::make_unique<TcpServer>("", 7780);
    tcpServer->InitServer();
}
    
void ServerApp::StartMainLoop() {
    std::cout << "INFO: ServerApp start\n";
    tcpServer->StartAccept();
}