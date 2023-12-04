//
// Created by Petia on 16.05.23.
//

#include "game_logic.h"

int check_winner(char board[3][3]) {
    // Проверка строк
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return (board[i][0] == 'X') ? PLAYER_X : PLAYER_O;
        }
    }

    // Проверка столбцов
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[0][j] == board[2][j]) {
            return (board[0][j] == 'X') ? PLAYER_X : PLAYER_O;
        }
    }

    // Проверка диагоналей
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return (board[0][0] == 'X') ? PLAYER_X : PLAYER_O;
    }

    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return (board[0][2] == 'X') ? PLAYER_X : PLAYER_O;
    }

    // Нет победителя, проверяем на ничью
    int total_moves = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ') {
                total_moves++;
            }
        }
    }

    if (total_moves == 9) {
        return DRAW;
    }

    // Игра продолжается
    return NO_WINNER;
}

int make_move(char board[3][3], int row, int col, int player) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
        return INVALID_MOVE;
    }

    board[row][col] = (player == PLAYER_X) ? 'X' : 'O';

    return SUCCESS_MOVE;
}

