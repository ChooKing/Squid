#ifndef SQUID_TEXT_H
#define SQUID_TEXT_H
#include <memory>
#include <string>
#include <SDL3/SDL.h>
#include "Font.h"

namespace squid {
    class Text {
        std::wstring text_;
        std::shared_ptr<Font> font_;
        //SDL_Texture* texture_ = nullptr;
        SDL_Renderer* renderer_ = nullptr;
        Buffer buffer_;
        //Coordinates are actually offsets relative to the window or other element
        int x_ = 0;
        int y_ = 0;
        SDL_FRect src_rect_ = {0, 0, 0, 0};
        SDL_FRect dst_rect_ = {0, 0, 0, 0};
        int required_width_ = 0;
        int required_height_ = 0;
        void measure_text();
        void render();
    public:
        Text(std::wstring text, const std::shared_ptr<Font> &font, SDL_Renderer* renderer);
        [[nodiscard]] Buffer get_buffer() const;

    };
}

#endif // SQUID_TEXT_H
