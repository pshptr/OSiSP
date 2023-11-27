#include "Graphics.h"
#include "GameBoard.h"
#include "Input.h"
#include "MainLoop.h"
#include <SDL2/SDL_ttf.h>
#include <string>

Graphics::Graphics() : window(nullptr), renderer(nullptr), isWindowOpen(false) {}

TTF_Font* font = TTF_OpenFont("fonts/DejaVuSans.ttf", 18);
//if (!font) {
//std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
// Дополнительная обработка ошибки при загрузке шрифта
// ...
//}

Graphics::~Graphics() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Graphics::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        return false;
    }

    isWindowOpen = true;
    return true;
}

void Graphics::Render(const GameBoard& gameBoard) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    DrawBoard(gameBoard);

    SDL_RenderPresent(renderer);
}

void Graphics::HandleEvents(GameBoard& gameBoard) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isWindowOpen = false;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            // Convert mouse coordinates to board coordinates
            int row = y / 160;
            int col = x / 160;

            if (gameBoard.IsCellEmpty(row, col) && !gameBoard.HasWinner()) {
                gameBoard.MakeMove(row, col, GameBoard::CellState::X);
            }
        }
    }
}

bool Graphics::IsWindowOpen() const {
    return isWindowOpen;
}

void Graphics::DrawBoard(const GameBoard& gameBoard) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            DrawCell(row, col, gameBoard.GetCellState(row, col));
        }
    }
}

void Graphics::DrawCell(int row, int col, GameBoard::CellState cellState) {
    SDL_Rect rect;
    rect.x = col * 160;
    rect.y = row * 160;
    rect.w = 160;
    rect.h = 160;

    if (cellState == GameBoard::CellState::X) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, rect.x + 20, rect.y + 20, rect.x + 140, rect.y + 140);
        SDL_RenderDrawLine(renderer, rect.x + 20, rect.y + 140, rect.x + 140, rect.y + 20);
    }
    else if (cellState == GameBoard::CellState::O) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderDrawLine(renderer, rect.x + 80, rect.y + 80, 60, 60);
    }
}