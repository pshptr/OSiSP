#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "GameBoard.h"

class Graphics {
public:
    Graphics();
    ~Graphics();

    bool Init();
    void Render(const GameBoard& gameBoard);
    void HandleEvents(GameBoard& gameBoard);
    bool IsWindowOpen() const;

    void renderGame(SDL_Renderer* renderer, const GameBoard& gameBoard);

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isWindowOpen;

    void DrawBoard(const GameBoard& gameBoard);
    void DrawCell(int row, int col, GameBoard::CellState cellState);
};

#endif // GRAPHICS_H