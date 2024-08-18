#include <winsock2.h>
#include "network.h"
#include <iostream>
#include <string>
// #pragma comment(lib, "ws2_32.lib") // Winsock Library

char Rbuffer[BUFFER_SIZE];
char Sbuffer[BUFFER_SIZE];

int Server::init(){
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "Failed. Error Code: " << WSAGetLastError() << std::endl;
        return 1;
    }
    std::cout<<"WSA Created"<<std::endl;
    // Create a socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Could not create socket. Error Code: " << WSAGetLastError() << std::endl;
        return 1;
    }
    std::cout<<"Socket Created"<<std::endl;
    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
    // Bind
    if (bind(serverSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cerr << "Bind failed. Error Code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout<<"Server Created"<<std::endl;
    return 0;
}

std::string Server::getIP(){
    // Get the local IP address
    if (gethostname(hostName, sizeof(hostName)) == SOCKET_ERROR) {
        std::cerr << "Error getting hostname: " << WSAGetLastError() << std::endl;
        return "";
    }

    hostEntry = gethostbyname(hostName);
    if (hostEntry == nullptr) {
        std::cerr << "Error getting host by name: " << WSAGetLastError() << std::endl;
        return "";
    }
    ipAddr = inet_ntoa(*(struct in_addr *)*hostEntry->h_addr_list);
    if (ipAddr == nullptr) {
        std::cerr << "Error converting IP address: " << WSAGetLastError() << std::endl;
        return "";
    }
    return ipAddr!=NULL? std::string(ipAddr): "";
}

int Server::connectClient(){
    // Listen for incoming connections
    listen(serverSocket, 1);
    int c = sizeof(struct sockaddr_in);
    clientSocket = accept(serverSocket, (struct sockaddr *)&client, &c);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed. Error Code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout<<"Client Connected"<<std::endl;
    return 0;
}

int Server::initialization(){
    init();
    IPaddress=getIP();
    connectClient();
    return 0;
}

int Server::sendData(){
    int recv_size = send(clientSocket, Sbuffer, BUFFER_SIZE, 0);
    if (recv_size == SOCKET_ERROR) {
            std::cerr << "recv failed. Error Code: " << WSAGetLastError() << std::endl;
            return 1;
    }
    ZeroMemory(Sbuffer, BUFFER_SIZE);
    return 0;
}

int Server::receiveData() {
    ZeroMemory(Rbuffer, BUFFER_SIZE);
    int recv_size = recv(clientSocket, Rbuffer, BUFFER_SIZE, 0);
    if (recv_size == SOCKET_ERROR) {
            std::cerr << "recv failed. Error Code: " << WSAGetLastError() << std::endl;
            return 1;
    }
    return 0;
}

int Server::close(){
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}

Server::~Server(){
    close();
}