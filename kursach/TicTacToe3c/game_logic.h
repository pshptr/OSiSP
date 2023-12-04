//
// Created by Petia on 16.05.23.
//

#ifndef TICTACTOE3C_GAME_LOGIC_H
#define TICTACTOE3C_GAME_LOGIC_H

enum GameResult {
    NO_WINNER,
    PLAYER1_WIN,
    PLAYER2_WIN,
    DRAW
};

#define PLAYER_X 1
#define PLAYER_O 2
#define DRAW 0

#define SUCCESS_MOVE 1
#define INVALID_MOVE 0

int check_winner(char board[3][3]);
int make_move(char board[3][3], int row, int col, int player);

#endif //TICTACTOE3C_GAME_LOGIC_H
