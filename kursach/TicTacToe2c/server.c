#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void play_game_server(int client_socket) {
    char board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
    };

    int row, col;
    int player = 1;
    int total_moves = 0;

    char message[256];

    while (total_moves < 9) {
        // Отправляем текущее состояние доски клиенту
        write(client_socket, board, sizeof(board));

        // Получаем ход от клиента
        if (read(client_socket, &row, sizeof(int)) < 0) {
            perror("Read error");
            exit(EXIT_FAILURE);
        }

        if (read(client_socket, &col, sizeof(int)) < 0) {
            perror("Read error");
            exit(EXIT_FAILURE);
        }

        // Проверяем валидность хода
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            strcpy(message, "Invalid move. Try again.");
            write(client_socket, message, sizeof(message));
            continue;
        }

        // Устанавливаем символ на доске
        board[row][col] = (player == 1) ? 'X' : 'O';
        total_moves++;

        // Проверяем условия победы
        int i, j;
        int win = 0;

        // Проверка строк
        for (i = 0; i < 3; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
                win = 1;
                break;
            }
        }

        // Проверка столбцов
        if (!win) {
            for (j = 0; j < 3; j++) {
                if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != ' ') {
                    win = 1;
                    break;
                }
            }
        }

        // Проверка диагоналей
        if (!win) {
            if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') ||
                (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')) {
                win = 1;
            }
        }

        // Проверка на ничью
        if (!win && total_moves == 9) {
            strcpy(message, "It's a draw!");
            write(client_socket, message, sizeof(message));
            break;
        }

        // Отправляем сообщение о результате игры
        if (win) {
        sprintf(message, "Player %d wins!", player);
        write(client_socket, message, sizeof(message));
        break;
        }
        // Переключаем игрока
        player = (player == 1) ? 2 : 1;
    }

// Закрываем сокет
    close(client_socket);
}

int mainn() {
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

    return 0;
}
