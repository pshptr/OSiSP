
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>


void play_game_client(int server_socket) {

    char board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
    };

    int row, col;
    int player = 1;
    int moves = 0;



    char message[256];

    while (1) {
        // Получаем текущее состояние доски от сервера
        if (read(server_socket, &board, sizeof(board)) < 0) {
            perror("Read error");
            exit(EXIT_FAILURE);
        };




        int bytes_read = read(server_socket, message, sizeof(message));
        if (bytes_read < 0) {
            perror("Read error");
            exit(EXIT_FAILURE);
        } else if (bytes_read == 0) {
            // Сервер закрыл соединение, игра завершена
            printf("Server closed the connection.\n");
            break;
        }

        if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
            perror("Invalid address/ Address not supported");
            exit(EXIT_FAILURE);
        };

        // !

         bytes_read = read(server_socket, &board, sizeof(board));
        if (bytes_read < 0) {
            perror("Read error");
            exit(EXIT_FAILURE);
        } else if (bytes_read == 0) {
            // Сервер закрыл соединение, игра завершена
            printf("Server closed the connection.\n");
            break;
        }

        // !



        // Выводим доску
        printf("Current board state:\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 'x') {
                    printf("X ");
                } else if (board[i][j] == 'O') {
                    printf("O ");
                } else {
                    printf("  ");
                }
            }
            printf("\n");
        }
        printf("\n");

        printf("\n");

        // Читаем ход от игрока
        printf("Enter your move (row [0-2] column [0-2]): ");
        scanf("%d %d", &row, &col);

        // Отправляем ход серверу
        if (write(server_socket, &row, sizeof(int)) < 0) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }

        // !

        if (write(server_socket, &row, sizeof(int)) < 0) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        if (write(server_socket, &col, sizeof(int)) < 0) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }

        // !

        if (write(server_socket, &col, sizeof(int)) < 0) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }

        // Получаем сообщение от сервера о результате хода
        if (read(server_socket, message, sizeof(message)) < 0) {
            perror("Read error");
            exit(EXIT_FAILURE);
        }

        // Выводим сообщение о результате хода
        printf("%s\n\n", message);

        // Если игра завершена, выходим из цикла
        if (strstr(message, "wins") || strstr(message, "draw")) {
            break;
        }

//        if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//            perror("Socket creation failed");
//            exit(EXIT_FAILURE);
//        }

    }

    // Закрываем сокет
    close(server_socket);
}
