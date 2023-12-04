
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void play_game_client(int server_socket) {
    char board[3][3];
    int row, col;
    char message[256];

    while (1) {
        // Получаем текущее состояние доски от сервера
        if (read(server_socket, board, sizeof(board)) < 0) {
            perror("Read error");
            exit(EXIT_FAILURE);
        }

        // Выводим доску
        printf("Current board state:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        // Читаем ход от игрока
        printf("Enter your move (row [0-2] column [0-2]): ");
        scanf("%d %d", &row, &col);

        // Отправляем ход серверу
        if (write(server_socket, &row, sizeof(int)) < 0) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }

        if (write(server_socket, &col, sizeof(int)) < 0) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }

        // Получаем сообщение от сервера о результате хода
        if (read(server_socket, message, sizeof(message)) < 0)
        {
            perror("Read error");
            exit(EXIT_FAILURE);
        }
        // Выводим сообщение о результате хода
        printf("%s\n\n", message);

        // Если игра завершена, выходим из цикла
        if (strstr(message, "wins") || strstr(message, "draw")) {
            break;
        }
    }

// Закрываем сокет
    close(server_socket);
}

int mainnn() {
    int sock = 0;
    struct sockaddr_in serv_addr;

// Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

// Преобразование IP-адреса из текстового формата в бинарный
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

// Установка соединения с сервером
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server.\n");

// Игра "Крестики-нолики" на стороне клиента
    play_game_client(sock);

    return 0;
}