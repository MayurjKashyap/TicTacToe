#pragma once
#include <winsock2.h>
#include <string>

#define BUFFER_SIZE 10
char buffer[BUFFER_SIZE];

class Network{
public:
    virtual ~Network() = default;
    virtual int sendData() = 0;
    virtual int receiveData() = 0;
    virtual int initialization() = 0;
    virtual int close() = 0;
    std::string IPaddress;
};

class Client: public Network{
public:
    ~Client();
    int init();
    int connectToServer(std::string s);
    int initialization() override;
    int sendData() override;
    int receiveData() override;
    int close() override;

private:
    WSADATA wsa;
    SOCKET clientSocket;
    struct sockaddr_in server;
};

class Server: public Network{
public:
    ~Server();
    int init();
    std::string getIP();
    int connectClient();
    int initialization() override;
    int sendData() override;
    int receiveData() override;
    int close() override;

private:
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in server, client;
    char hostName[256];
    char *ipAddr;
    struct hostent *hostEntry;
};