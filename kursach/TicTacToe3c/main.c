

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void play_game_server(int client_socket);
void play_game_client(int server_socket);

int main() {
    int mode;

    printf("Tic-Tac-Toe Game\n");
    printf("1. Play as server\n");
    printf("2. Play as client\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &mode);

    if (mode == 1) {
        // Запуск в режиме сервера
        int server_fd, new_socket;
        struct sockaddr_in address;
        int addrlen = sizeof(address);

        // Создание сокета
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        // Привязка сокета к IP-адресу и порту
        if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
            perror("Bind failed");
            exit(EXIT_FAILURE);
        }

        // Ожидание подключения клиента
        if (listen(server_fd, 3) < 0) {
            perror("Listen failed");
            exit(EXIT_FAILURE);
        }

        printf("Waiting for a client to connect...\n");

        // Принятие подключения от клиента
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        printf("Client connected.\n");

        // Игра "Крестики-нолики" на стороне сервера
        play_game_server(new_socket);

        // Закрытие сокета сервера
        close(server_fd);
    } else if (mode == 2) {
        sleep(1);
        // Запуск в режиме клиента
        int client_fd;
        struct sockaddr_in server_address;

        // Создание сокета
        if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORT);

        // Преобразование IP-адреса из текстового вида в структуру sockaddr_in
        if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
            perror("Invalid address/ Address not supported");
            exit(EXIT_FAILURE);
        }

        // Подключение к серверу
        if (connect(client_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
            perror("Connection failed");
            exit(EXIT_FAILURE);
        }

        printf("Connected to the server.\n");

        // Игра "Крестики-нолики" на стороне клиента
        play_game_client(client_fd);

        // Закрытие сокета клиента
        close(client_fd);
    } else {
        printf("Invalid choice. Exiting.\n");
    }

    return 0;
}

int check_winner(char board[3][3]) {
    // Проверка по горизонтали
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return 1;
    }

    // Проверка по вертикали
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ')
            return 1;
    }

    // Проверка по диагоналям
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' '))
        return 1;

    return 0;
}


void play_game_server(int client_socket) {
    // Реализация игры "Крестики-нолики" на стороне сервера
    // ваш код здесь
}

void play_game_client(int server_socket) {
    // Реализация игры "Крестики-нолики" на стороне клиента
    // ваш код здесь
}














//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <unistd.h>
//
//#define PORT 8080
//
//void play_game_server(int client_socket);
//void play_game_client(int server_socket);
//
//int main() {
//
//    int mode;
//
//    printf("Tic-Tac-Toe Game\n");
//    printf("1. Play as server\n");
//    printf("2. Play as client\n");
//    printf("Enter your choice (1-2): ");
//    scanf("%d", &mode);
//
//    if (mode == 1) {
//        // Запуск в режиме сервера
//        int server_fd, new_socket;
//        // Ваш код для сервера
//        play_game_server(new_socket);
//    } else if (mode == 2) {
//        sleep(1);
//        // Запуск в режиме клиента
//        int client_fd;
//        // Ваш код для клиента
//        play_game_client(client_fd);
//    } else {
//        printf("Invalid choice. Exiting...\n");
//        return 1;
//    }
//
//
//
//    int server_fd, new_socket;
//    struct sockaddr_in address;
//    int addrlen = sizeof(address);
//
//    // Создание сокета
//    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//        perror("Socket creation failed");
//        exit(EXIT_FAILURE);
//    }
//
//    address.sin_family = AF_INET;
//    address.sin_addr.s_addr = INADDR_ANY;
//    address.sin_port = htons(PORT);
//
//    // Привязка сокета к IP-адресу и порту
//    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
//        perror("Bind failed");
//        exit(EXIT_FAILURE);
//    }
//
//    // Ожидание подключения клиента
//    if (listen(server_fd, 3) < 0) {
//        perror("Listen failed");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Waiting for a client to connect...\n");
//
//    // Принятие подключения от клиента
//    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
//        perror("Accept failed");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Client connected.\n");
//
//    // Игра "Крестики-нолики" на стороне сервера
//    play_game_server(new_socket);
//
//    // Закрытие сокета сервера
//    close(server_fd);
//
//    return 0;
//}











//void readSocket(int socket, void *buffer, size_t length) {
//    size_t bytesRead = 0;
//    while (bytesRead < length) {
//        ssize_t result = read(socket, buffer + bytesRead, length - bytesRead);
//        if (result < 0) {
//            perror("Ошибка чтения из сокета");
//            exit(EXIT_FAILURE);
//        } else if (result == 0) {
//            fprintf(stderr, "Соединение разорвано\n");
//            exit(EXIT_FAILURE);
//        }
//        bytesRead += result;
//    }
//}
//
//
//int main(void) {
//
//
//
//
//    int serverSocket, clientSocket;
//    struct sockaddr_in serverAddress, clientAddress;
//    socklen_t clientLength;
//
//    // Создание сокета
//    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//    if (serverSocket == -1) {
//        perror("Ошибка создания сокета");
//        exit(EXIT_FAILURE);
//    }
//
//    // Настройка адреса сервера
//    serverAddress.sin_family = AF_INET;
//    serverAddress.sin_port = htons(8080);
//    serverAddress.sin_addr.s_addr = INADDR_ANY;
//
//    // Привязка сокета к адресу
//    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
//        perror("Ошибка привязки сокета");
//        exit(EXIT_FAILURE);
//    }
//
//    // Ожидание подключения клиента
//    if (listen(serverSocket, 1) == -1) {
//        perror("Ошибка ожидания подключения");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Сервер ожидает подключения...\n");
//
//    // Принятие подключения от клиента
//    clientLength = sizeof(clientAddress);
//    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientLength);
//    if (clientSocket == -1) {
//        perror("Ошибка принятия подключения");
//        exit(EXIT_FAILURE);
//    }
//
//    printf("Клиент подключен\n");
//
//
//
//









////#include <stdio.h>
////#include <stdlib.h>
////#include <string.h>
////#include <sys/socket.h>
////#include <arpa/inet.h>
////#include <unistd.h>
////
////#define PORT 8080
////#define PORT1 8081
////
////void play_game_server(int client_socket);
////
////int main() {
////
////    int server_fd, new_socket;
////    struct sockaddr_in address;
////    int addrlen = sizeof(address);
////
////    // Создание сокета
////    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
////        perror("Socket creation failed");
////        exit(EXIT_FAILURE);
////    }
////
////    address.sin_family = AF_INET;
////    address.sin_addr.s_addr = INADDR_ANY;
////    address.sin_port = htons(PORT);
////
////    // Привязка сокета к IP-адресу и порту
////    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
////        perror("Bind failed");
////        exit(EXIT_FAILURE);
////    }
////
////    // Ожидание подключения клиента
////    if (listen(server_fd, 3) < 0) {
////        perror("Listen failed");
////        exit(EXIT_FAILURE);
////    }
////
////    printf("Waiting for a client to connect...\n");
////
////    // Принятие подключения от клиента
////    if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
////        perror("Accept failed");
////        exit(EXIT_FAILURE);
////    }
////
////    printf("Client connected.\n");
////
////    // Игра "Крестики-нолики" на стороне сервера
////    play_game_server(new_socket);
////
////    // Закрытие сокета сервера
////    close(server_fd);
////
////    return 0;
////}
