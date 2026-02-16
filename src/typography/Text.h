#ifndef SQUID_TEXT_H
#define SQUID_TEXT_H
#include <memory>
#include <string>
#include <SDL3/SDL.h>
#include "Font.h"
#include "../Node.h"

namespace squid {
    class Text: Node {
        std::wstring text_;
        std::shared_ptr<Font> font_;
        SDL_Renderer* renderer_ = nullptr;
        Buffer buffer_;
        //Coordinates are actually offsets relative to the window or other element
        int x_ = 0;
        int y_ = 0;
        SDL_FRect src_rect_ = {0, 0, 0, 0};
        SDL_FRect dst_rect_ = {0, 0, 0, 0};
        void measure() override;
        void render();
    public:
        Text(std::wstring text, const std::shared_ptr<Font> &font, SDL_Renderer* renderer);
        [[nodiscard]] Buffer get_buffer() const;

    };
}

#endif // SQUID_TEXT_H
