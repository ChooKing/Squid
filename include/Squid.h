//
// Created by standard on 2/9/2026.
//

#ifndef SQUID_SQUID_H
#define SQUID_SQUID_H
#include <SDL3/SDL.h>
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include "../src/AppWindow.h"

class Squid {
    std::shared_ptr<AppWindow> main_window_{};
    std::unordered_map<SDL_WindowID, std::shared_ptr<AppWindow>> windows_{};
    std::map<std::pair<SDL_EventType, SDL_WindowID>, std::vector<std::function<void(SDL_Event &)>>>
      eventListeners_{};
public:
    Squid();
    void add_event_listener(SDL_EventType e, SDL_WindowID w,
                        const std::function<void(SDL_Event&)>& callback);
    std::shared_ptr<AppWindow> create_window(const std::string& title, int w, int h, SDL_WindowFlags flags);
    void run(const std::function<void()>& runner);
};


#endif // SQUID_SQUID_H
