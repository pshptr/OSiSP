#pragma once

#include <iostream>
#include <string>
#include <thread>
#include "GameBoard.h"

#ifdef _WIN32
#include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#endif

class Network {
public:
    Network();
    ~Network();

    bool sendPacket(SOCKET socket, const std::string& packet); // Объявление функции sendPacket
    bool Network::receivePacket(std::string& packet);
    void closeSocket(SOCKET socket); // Объявление функции closeSocket

    bool initializeServer(int port);
    bool initializeClient(const std::string& ipAddress, int port);
    bool isConnected() const;

    bool sendPacket(const std::string& packet);
    bool receivePacket(SOCKET clientSocket, std::string& packet);

private:

    GameBoard gameBoard;

    bool initializeWinsock();
    void acceptConnections();
    void handleClient(SOCKET clientSocket);

    bool isServer;
    bool connected;

    SOCKET serverSocket;
    SOCKET clientSocket;

    std::thread acceptThread;
};
