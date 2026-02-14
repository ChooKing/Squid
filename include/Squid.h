#ifndef SQUID_SQUID_H
#define SQUID_SQUID_H
#include <SDL3/SDL.h>
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include "../src/AppWindow.h"
#include "../src/typography/Font.h"
#include "../src/typography/Text.h"
namespace squid {
    class Squid {
        std::shared_ptr<AppWindow> main_window_{};
        std::shared_ptr<SDL_Surface> main_surface_{};
        std::unordered_map<SDL_WindowID, std::shared_ptr<AppWindow>> windows_{};
        std::map<std::pair<SDL_EventType, SDL_WindowID>, std::vector<std::function<void(SDL_Event &)>>>
                eventListeners_{};
        std::shared_ptr<Font> font_{};

    public:
        Squid();
        void add_event_listener(SDL_EventType e, SDL_WindowID w, const std::function<void(SDL_Event &)> &callback);
        std::shared_ptr<Text> create_text(const std::wstring& text, SDL_Renderer* renderer);
        std::shared_ptr<AppWindow> create_window(const std::string &title, int w, int h, SDL_WindowFlags flags);
        void run(const std::function<void()> &runner);
        void set_font(const std::shared_ptr<Font> &font);
    };
} // namespace squid

#endif // SQUID_SQUID_H
