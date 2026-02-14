#ifndef SQUID_APPWINDOW_H
#define SQUID_APPWINDOW_H

#include <SDL3/SDL.h>
#include <string>

class AppWindow {
    int width;
    int height;
    SDL_Window* window_ = nullptr;
    SDL_Surface* surface_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

public:
    AppWindow(const std::string& title, int w, int h, SDL_WindowFlags flags);
    void redraw() const;
    [[nodiscard]] SDL_WindowID getId() const;
    [[nodiscard]] SDL_Renderer* getRenderer() const;
    [[nodiscard]] SDL_Surface* getSurface() const;

};


#endif // SQUID_APPWINDOW_H
