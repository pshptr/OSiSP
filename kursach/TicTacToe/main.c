#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 3

char board[BOARD_SIZE][BOARD_SIZE];

void initialize_board() {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void print_board() {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
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
}

int is_board_full() {
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

char check_winner() {
    int i;

    // Проверка строк
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }

    // Проверка столбцов
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return board[0][i];
        }
    }

    // Проверка диагоналей
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return board[0][0];
    }

    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return board[0][2];
    }

    return ' ';
}

int make_move(int row, int col, char symbol) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ') {
        return 0;
    }

    board[row][col] = symbol;
    return 1;
}

int main() {
    int row, col;
    char symbol = 'X';

    initialize_board();

    while (1) {
        print_board();

        printf("Player %c, enter your move (row [0-2] column [0-2]): ", symbol);
        scanf("%d %d", &row, &col);

        if (!make_move(row, col, symbol)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

        char winner = check_winner();
        if (winner != ' ') {
            print_board();
            printf("Player %c wins!\n", winner);
            break;
        }

        if (is_board_full()) {
            print_board();
            printf("It's a tie!\n");
            break;
        }

        // Switch player
        symbol = (symbol == 'X') ? 'O' : 'X';
    }

    return 0;
}
