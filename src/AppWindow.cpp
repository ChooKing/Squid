#include "AppWindow.h"
#include <stdexcept>

AppWindow::AppWindow(const std::string& title, const int w, const int h,
                     const SDL_WindowFlags flags)
    : width(w), height(h) {
    if (!SDL_CreateWindowAndRenderer(title.c_str(), w, h, flags, &this->window_,
                                     &this->renderer_)) {
        throw std::runtime_error("Window could not be created!");
                                     }
    SDL_SetRenderLogicalPresentation(this->renderer_, w, h,
                                     SDL_LOGICAL_PRESENTATION_DISABLED);
    SDL_SetRenderDrawColor(this->renderer_, 64, 64, 86, 255);
    this->surface_ = SDL_GetWindowSurface(this->window_);
    this->redraw();
}
void AppWindow::redraw() const {
    SDL_RenderClear(this->renderer_);
    SDL_RenderPresent(this->renderer_);
}
SDL_Renderer* AppWindow::getRenderer() const { return this->renderer_; }
SDL_WindowID AppWindow::getId() const {
    return SDL_GetWindowID(this->window_);
}