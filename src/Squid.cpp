#include "../include/Squid.h"

#include <iostream>
#include <ostream>
namespace squid {
    Squid::Squid() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error("SDL could not initialize!");
        }
    }
    void Squid::add_event_listener(SDL_EventType e, SDL_WindowID w, const std::function<void(SDL_Event &)> &callback) {
        const auto event_window = std::pair{e, w};
        if (const auto listener = eventListeners_.find(event_window); listener != eventListeners_.end()) {
            listener->second.push_back(callback);
        } else {
            eventListeners_[event_window] = {callback};
        }
    }
    std::shared_ptr<Text> Squid::create_text(const std::wstring &text, SDL_Renderer* renderer) { return std::make_shared<Text>(text, font_, renderer); }

    std::shared_ptr<AppWindow> Squid::create_window(const std::string &title, int w, int h, SDL_WindowFlags flags) {
        const auto window = new AppWindow(title, w, h, flags);
        auto shared_window = std::shared_ptr<AppWindow>(window);
        auto id = window->getId();
        if (main_window_ == nullptr) {
            main_window_ = shared_window;
        } else {
            windows_.insert({id, shared_window});
        }

        return shared_window;
    }
    void Squid::run(const std::function<void()> &runner) {
        SDL_Event e;
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_EVENT_QUIT)
                    quit = true;
                else {
                    auto window_id = e.window.windowID;
                    if (auto listeners = eventListeners_.find(std::pair{static_cast<SDL_EventType>(e.type), window_id});
                        listeners != eventListeners_.end()) {
                        for (const auto &listener: listeners->second) {
                            listener(e);
                        }
                    } else if (e.type == SDL_EVENT_WINDOW_RESIZED) {
                        if (auto window = windows_.find(window_id); window != windows_.end()) {
                            window->second->redraw();
                            std::cout << "Window resized to " << e.window.data1 << "x" << e.window.data2 << std::endl;
                        }
                    }
                    runner();
                }
            }
        }
    }
    void Squid::set_font(const std::shared_ptr<Font> &font) { font_ = font; }
} // namespace squid
