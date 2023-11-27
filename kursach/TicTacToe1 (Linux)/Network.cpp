#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>

#include "Network.h"

#ifdef _WIN32
#include <ws2tcpip.h>
#include <winsock2.h>
#else
#include <cstring>
#endif



bool Network::sendPacket(SOCKET socket, const std::string& packet) {
    if (!connected) {
        std::cout << "Not connected to a server.\n";
        return false;
    }

    int result = send(socket, packet.c_str(), packet.length(), 0);
    if (result == -1) {
        std::cout << "Failed to send packet.\n";
        return false;
    }

    return true;
}

void Network::closeSocket(SOCKET socket) {
#ifdef _WIN32
    closesocket(socket);
#else
    close(socket);
#endif
}





Network::Network() : isServer(false), connected(false), serverSocket(INVALID_SOCKET), clientSocket(INVALID_SOCKET) {}

Network::~Network() {
    if (connected) {
#ifdef _WIN32
        closesocket(serverSocket);
            closesocket(clientSocket);
            WSACleanup();
#else
        close(serverSocket);
        close(clientSocket);
#endif
    }
}

bool Network::initializeServer(int port) {
    if (connected) {
        std::cout << "Already connected to a server or running as a server.\n";
        return false;
    }

    if (!initializeWinsock()) {
        std::cout << "Failed to initialize Winsock.\n";
        return false;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "Failed to create server socket.\n";
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cout << "Failed to bind server socket.\n";
        return false;
    }

    if (listen(serverSocket, SOMAXCONN) == -1) {
        std::cout << "Failed to listen on server socket.\n";
        return false;
    }

    std::cout << "Waiting for client connections...\n";
    acceptThread = std::thread(&Network::acceptConnections, this);

    isServer = true;
    connected = true;
    return true;
}

bool Network::initializeClient(const std::string& ipAddress, int port) {
    if (connected) {
        std::cout << "Already connected to a server or running as a server.\n";
        return false;
    }

    if (!initializeWinsock()) {
        std::cout << "Failed to initialize Winsock.\n";
        return false;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Failed to create client socket.\n";
        return false;
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);

    // Convert IP address from string to binary format
    if (inet_pton(AF_INET, ipAddress.c_str(), &(serverAddress.sin_addr)) <= 0) {
        std::cout << "Invalid IP address.\n";
        return false;
    }

    if (connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cout << "Failed to connect to server.\n";
        return false;
    }

    connected = true;
    return true;
}

bool Network::isConnected() const {
    return connected;
}

bool Network::sendPacket(const std::string& packet) {
    if (!connected) {
        std::cout << "Not connected to a server.\n";
        return false;
    }

    int result = send(isServer ? clientSocket : serverSocket, packet.c_str(), packet.length(), 0);
    if (result == -1) {
        std::cout << "Failed to send packet.\n";
        return false;
    }

    return true;
}

bool Network::receivePacket(std::string& packet) {
    if (!connected) {
        std::cout << "Not connected to a server.\n";
        return false;
    }

    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));

    int result = recv(isServer ? clientSocket : serverSocket, buffer, sizeof(buffer), 0);
    if (result == -1) {
        std::cout << "Failed to receive packet.\n";
        return false;
    }

    packet = buffer;
    return true;
}

bool Network::initializeWinsock() {
#ifdef _WIN32
    WSADATA wsData;
    return WSAStartup(MAKEWORD(2, 2), &wsData) == 0;
#else
    return true; // No additional setup needed for other platforms
#endif
}

void Network::acceptConnections() {
    sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);

    clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), reinterpret_cast<socklen_t*>(&clientAddressSize));
    if (clientSocket != INVALID_SOCKET) {
        std::cout << "Client connected.\n";
        handleClient(clientSocket);
    }
}





void Network::handleClient(SOCKET clientSocket) {
    // Initialize playerSymbol variable
    char playerSymbol = playerSymbol;

    while (true) {
        std::string packet;
        if (!receivePacket(clientSocket, packet)) {
            break;
        }

        if (packet == "MOVE") {
            // Receive move data from the client
            //int row, col;
            //if (!receiveMoveData(clientSocket, row, col)) {
            //  break;
            //}
            std::string packet;
            if (!receivePacket(packet)) {
                break;
            }

            if (packet == "MOVE") {
                // Parcing paketa dlya poluchenia dannix o dvixhenii
                // Primer: "MOVE|<row><col>"
                std::stringstream iss(packet);
                std::string moveToken;
                std::getline(iss, moveToken, '|');
                std::getline(iss, moveToken, '|');
                int row = std::stoi(moveToken, '|');
                std::getline(iss, moveToken, '|');
                int col = std::stoi(moveToken);


                //Obnovlenie sostoiania igri na osnove poluchennih dannih o dvizhenii
                gameBoard.MakeMove(row, col, playerSymbol);

                //proverka, okonchena li igra
                if (gameBoard.IsGameOver()) {
                    sendPacket("GAME_OVER");
                    break;
                }

                //Otpravka podtverzhdenia klientu
                sendPacket("MOVE_CONFIRMED");
            }


            // Update the game state based on the received move data
            gameBoard.MakeMove(row, col, playerSymbol);

            // Check if the game is over
            if (gameBoard.IsGameOver()) {
                sendPacket(clientSocket, "GAME_OVER");
                break;
            }

            // Send confirmation back to the client
            sendPacket(clientSocket, "MOVE_CONFIRMED");
        }
        else if (packet == "GAME_OVER") {
            // Handle game over packet
            // Perform necessary actions when the game is over
            // ...

            // Send confirmation back to the client
            sendPacket(clientSocket, "GAME_OVER_CONFIRMED");
            break;
        }
        // Add more conditions to handle other types of packets as needed
    }

    // Close the client socket
    close(clientSocket);
}




//void Network::handleClient(SOCKET clientSocket) {

  //  char playerSymbol = playerSymbol;

    //while (true) {
      //  std::string packet;
        //if (!receivePacket(clientSocket, packet)) {
          //  break;
        //}

        //if (packet == "MOVE") {
            // Receive move data from the client
          //  int row, col;
            //if (!receiveMoveData(clientSocket, row, col)) {
              //  break;
            //}

            // Update the game state based on the received move data
            //gameBoard.makeMove(row, col, playerSymbol);

            // Check if the game is over
            //if (gameBoard.isGameOver()) {
              //  sendPacket(clientSocket, "GAME_OVER");
                //break;
            //}

            // Send confirmation back to the client
            //sendPacket(clientSocket, "MOVE_CONFIRMED");
        //}
        //else if (packet == "GAME_OVER") {
            // Handle game over packet
            // Perform necessary actions when the game is over
            // ...

            // Send confirmation back to the client
          //  sendPacket(clientSocket, "GAME_OVER_CONFIRMED");
            //break;
        //}
        // Add more conditions to handle other types of packets as needed
    //}

    // Close the client socket
//    closesocket(clientSocket);
//}