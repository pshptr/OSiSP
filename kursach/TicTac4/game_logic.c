#include "game_logic.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

void read_socket(int socket, void *buffer, size_t length) {
    size_t bytesRead = 0;
    while (bytesRead < length) {
        ssize_t result = read(socket, buffer + bytesRead, length - bytesRead);
        if (result < 0) {
            perror("Ошибка чтения из сокета");
            exit(EXIT_FAILURE);
        } else if (result == 0) {
            fprintf(stderr, "Соединение разорвано\n");
            exit(EXIT_FAILURE);
        }
        bytesRead += result;
    }
}

void write_socket(int socket, const void *buffer, size_t length) {
    size_t bytesWritten = 0;
    while (bytesWritten < length) {
        ssize_t result = write(socket, buffer + bytesWritten, length - bytesWritten);
        if (result < 0) {
            perror("Ошибка записи в сокет");
            exit(EXIT_FAILURE);
        }
        bytesWritten += result;
    }
}

void initialize_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void print_board(const char board[BOARD_SIZE][BOARD_SIZE]) {
    printf("Current board state:\n\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) {
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

int make_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int column, char mark) {
    if (row < 0 || row >= BOARD_SIZE || column < 0 || column >= BOARD_SIZE) {
        return 0;  // Invalid move
    }

    if (board[row][column] != ' ') {
        return 0;  // Cell already occupied
    }

    board[row][column] = mark;
    return 1;  // Valid move
}

// bool check_win(const char board[BOARD_SIZE][BOARD_SIZE], char mark) {
//    // Проверка выигрышных комбинаций по строкам
//    for (int row = 0; row < BOARD_SIZE; ++row) {
//        if (board[row][0] == mark && board[row][1] == mark && board[row][2] == mark)
//            return true;
//    }
//
//    // Проверка выигрышных комбинаций по столбцам
//    for (int col = 0; col < BOARD_SIZE; ++col) {
//        if (board[0][col] == mark && board[1][col] == mark && board[2][col] == mark)
//            return true;
//    }
//
//    // Проверка выигрышных комбинаций по диагоналям
//    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark)
//        return true;
//
//    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark)
//        return true;
//
//    return false;  // Нет выигрышной комбинации
//}
