#include "Input.h"

Input::Input()
        : quitRequested(false),
          mouseButtonDown(false),
          mouseButtonUp(false),
          mouseClicked(false),
          mouseReleased(false),
          mouseX(0),
          mouseY(0) {}

void Input::processInput(SDL_Event&) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            processMouseEvent(event);
            mouseButtonDown = true;
            mouseClicked = true;
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            processMouseEvent(event);
            mouseButtonUp = true;
            mouseReleased = true;
        } else if (event.type == SDL_MOUSEMOTION) {
            mouseX = event.motion.x;
            mouseY = event.motion.y;
        }
    }
}

bool Input::isQuitRequested() const {
    return quitRequested;
}

bool Input::isMouseButtonDown() const {
    return mouseButtonDown;
}

bool Input::isMouseButtonUp() const {
    return mouseButtonUp;
}

bool Input::isMouseClicked() const {
    return mouseClicked;
}

bool Input::isMouseReleased() const {
    return mouseReleased;
}

int Input::getMouseX() const {
    return mouseX;
}

int Input::getMouseY() const {
    return mouseY;
}

void Input::processMouseEvent(const SDL_Event& event) {
    mouseX = event.button.x;
    mouseY = event.button.y;
}

void Input::processKeyboardEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_q:
                quitRequested = true;
                break;
                // Добавьте обработку других клавиш по необходимости
        }
    }
}