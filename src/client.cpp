#include <winsock2.h>
#include "network.h"
#include <iostream>
#include <string>
// #pragma comment(lib, "ws2_32.lib") // Winsock Library

int Client::init(){
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Failed. Error Code: " << WSAGetLastError() << std::endl;
        return 1;
    }
    std::cout<<"WSA Created"<<std::endl;
    // Create a socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
    std::cerr << "Could not create socket. Error Code: " << WSAGetLastError() << std::endl;
    return 1;
    }
    std::cout<<"CSocket Created"<<std::endl;
    return 0;
}

int Client::connectToServer(std::string s){
    // Specify server address
    server.sin_addr.s_addr = inet_addr(s.basic_string::c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        std::cerr << "Connect failed. Error Code: " << WSAGetLastError() << std::endl;
        return 1;
    }
    std::cout<<"Server Connected"<<std::endl;
    return 0;    
}

int Client::initialization(){
    init();
    connectToServer(IPaddress);
    return 0;
}

int Client::sendData(){
    if (send(clientSocket, buffer, BUFFER_SIZE, 0) < 0) {
        std::cerr << "Send failed. Error Code: " << WSAGetLastError() << std::endl;
        return 1;
    }
    ZeroMemory(buffer, BUFFER_SIZE);
    return 0;
}

int Client::receiveData() {
    ZeroMemory(buffer, BUFFER_SIZE);
    int recv_size = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (recv_size == SOCKET_ERROR) {
            std::cerr << "recv failed. Error Code: " << WSAGetLastError() << std::endl;
            return 1;
    }
    std::cout<<buffer<<std::endl;
    return 0;
}

int Client::close(){
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}

Client::~Client(){
    close();
}
