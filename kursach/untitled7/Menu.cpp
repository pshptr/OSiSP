#include "Menu.h"

#include <SDL_ttf.h> // Заголовочный файл для работы с библиотекой TTF

// Загрузка шрифта
TTF_Font* font = TTF_OpenFont("fonts/DejaVuSans.ttf", 18);

Menu::Menu() {}

void Menu::addButton(const std::string& text, std::function<void()> onClick) {
    Button button;
    button.text = text;
    button.onClick = onClick;
    buttons.push_back(button);
}

void Menu::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (const Button& button : buttons) {
        SDL_RenderDrawRect(renderer, &button.rect);

        SDL_Surface* surface = TTF_RenderText_Solid(font, button.text.c_str(), { 0, 0, 0 });
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        int textWidth, textHeight;
        SDL_QueryTexture(texture, NULL, NULL, &textWidth, &textHeight);

        int textX = button.rect.x + (button.rect.w - textWidth) / 2;
        int textY = button.rect.y + (button.rect.h - textHeight) / 2;

        SDL_Rect textRect = { textX, textY, textWidth, textHeight };
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}

void Menu::handleMouseClick(int x, int y) {
    for (const Button& button : buttons) {
        if (x >= button.rect.x && x < button.rect.x + button.rect.w &&
            y >= button.rect.y && y < button.rect.y + button.rect.h) {
            button.onClick();
            break;
        }
    }
}