#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class Input {
public:
    Input();

    void processInput(SDL_Event&);

    bool isQuitRequested() const;

    bool isMouseButtonDown() const;
    bool isMouseButtonUp() const;
    bool isMouseClicked() const;
    bool isMouseReleased() const;
    int getMouseX() const;
    int getMouseY() const;

private:
    bool quitRequested;
    bool mouseButtonDown;
    bool mouseButtonUp;
    bool mouseClicked;
    bool mouseReleased;
    int mouseX;
    int mouseY;

    void processMouseEvent(const SDL_Event& event);
    void processKeyboardEvent(const SDL_Event& event);
};

#endif