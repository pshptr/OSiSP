#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <string>

class GameBoard {
public:
    enum class CellState { Empty, X, O };

    GameBoard();

    void updateBoard();

    void Reset();
    CellState GetCellState(int row, int col) const;
    bool IsCellEmpty(int row, int col) const;
    bool IsFull() const;
    bool HasWinner() const;
    CellState GetWinner() const;
    bool MakeMove(int row, int col, CellState player);

private:
    std::vector<std::vector<CellState>> board;
    CellState winner;
};

#endif // GAMEBOARD_H