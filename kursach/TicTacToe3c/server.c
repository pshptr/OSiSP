

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "game_logic.h"

void play_game_server(int client_socket) {
    char board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
    };

    // !

    int board_size = 3;
    write(client_socket, &board_size, sizeof(int));
    write(client_socket, &board, sizeof(board));

    // !

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }


    int row, col;
    int player = 1;
    int total_moves = 0;

    char message[256];

    while (total_moves < 9) {
        // Отправляем текущее состояние доски клиенту
        write(client_socket, &board, sizeof(board));

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

        // !

        if (write(client_socket, message, sizeof(message)) < 0) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }

        // !

        // Переключаем игрока
        player = (player == 1) ? 2 : 1;
    }

    const int server_socket;
    close(server_socket);


    // Закрываем сокет
    close(client_socket);
}
