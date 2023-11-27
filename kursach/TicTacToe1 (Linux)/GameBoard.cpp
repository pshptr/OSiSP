#include "GameBoard.h"

GameBoard::GameBoard() {
    Reset();
}

void GameBoard::Reset() {
    board.resize(3, std::vector<CellState>(3, CellState::Empty));
    winner = CellState::Empty;
}

GameBoard::CellState GameBoard::GetCellState(int row, int col) const {
    return board[row][col];
}

bool GameBoard::IsCellEmpty(int row, int col) const {
    return board[row][col] == CellState::Empty;
}

bool GameBoard::IsFull() const {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == CellState::Empty) {
                return false;
            }
        }
    }
    return true;
}

bool GameBoard::HasWinner() const {
    return winner != CellState::Empty;
}

GameBoard::CellState GameBoard::GetWinner() const {
    return winner;
}

bool GameBoard::MakeMove(int row, int col, CellState player) {
    if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != CellState::Empty) {
        return false;
    }

    board[row][col] = player;

    // Check for a winning move
    for (int i = 0; i < 3; ++i) {
        // Check rows and columns
        if (board[row][i] != player || board[i][col] != player) {
            break;
        }
        if (i == 2) {
            winner = player;
            return true;
        }
    }

    // Check diagonals
    if (row == col || row + col == 2) {
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
            winner = player;
            return true;
        }
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
            winner = player;
            return true;
        }
    }

    return false;
}