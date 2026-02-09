#include <iostream>
#include "../include/Squid.h"
int main() {
    const auto squid = new Squid();
    const auto window = squid->create_window("testwindow", 1920, 1080, SDL_WINDOW_RESIZABLE);
    auto renderer = window.get()->getRenderer();
    auto runner = [&]() {
        //SDL_RenderClear(renderer);

        //SDL_RenderPresent(renderer);
    };
    squid->run(runner);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
