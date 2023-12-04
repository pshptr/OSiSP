#ifndef MAINLOOP_H
#define MAINLOOP_H

#include <SDL.h>
#include <SDL2/SDL.h>
#include "GameBoard.h"
#include "Menu.h"
#include "Network.h"
#include "Input.h"
#include "Graphics.h"

class MainLoop {
public:
    MainLoop();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Input input;
    Graphics graphics;
    bool isRunning;

    void processEvents();
    void update();
    void render();
};

#endif // MAINLOOP_H