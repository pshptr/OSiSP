#include "MainLoop.h"
#include "Input.h"
#include "GameBoard.h"
#include "Graphics.h"

MainLoop::MainLoop() : isRunning(false) {
}

void MainLoop::run() {

    GameBoard gameBoard;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    isRunning = true;
    while (isRunning) {
        processEvents();
        update();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void MainLoop::processEvents() {

    GameBoard gameBoard;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }

        input.processInput(event);
    }
}

void MainLoop::update() {

    GameBoard gameBoard;

    // Добавьте обновление состояния игры по необходимости
    gameBoard.updateBoard();
}

void MainLoop::render() {

    GameBoard gameBoard;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    graphics.renderGame(renderer, gameBoard);

    SDL_RenderPresent(renderer);
}