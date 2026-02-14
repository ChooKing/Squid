#include <iostream>
#include "../include/Squid.h"
#include "../src/typography/Text.h"
int main() {
    const auto squid = new squid::Squid();
    const auto window = squid->create_window("testwindow", 1920, 1080, SDL_WINDOW_RESIZABLE);
    const auto renderer = window.get()->getRenderer();
    //auto surface = window.get()->getSurface();
    squid->set_font(std::make_shared<squid::Font>(squid::Font("assets/fonts/OpenSans.ttf", 48)));
    const auto text = squid->create_text(L"SDL greatly helps!");

    auto runner = [&]() {
        SDL_RenderClear(renderer);
        text->draw(renderer);
        SDL_RenderPresent(renderer);
    };
    squid->run(runner);
    return 0;
}
