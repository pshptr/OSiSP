#pragma once

#include <functional>
#include <string>
#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class Menu {
public:
    Menu();

    void addButton(const std::string& text, std::function<void()> onClick);

    void render(SDL_Renderer* renderer);
    void handleMouseClick(int x, int y);

private:
    struct Button {
        std::string text;
        std::function<void()> onClick;
        SDL_Rect rect;
    };

    std::vector<Button> buttons;
};