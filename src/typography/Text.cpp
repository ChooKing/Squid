#include "Text.h"

#include <iostream>
#include <ostream>
#include <utility>
namespace squid {
    Text::Text(std::wstring text, const std::shared_ptr<Font> &font): text_(std::move(text)), font_(font) {}
    void Text::draw(SDL_Renderer *renderer) const {
        int required_width = 0;
        int max_row = 0;
        for (const auto c : text_) {
            const auto character = font_->get_character(c);
            required_width += (character->metrics.horiAdvance) / 64;
            if (character->rows > max_row) {
                max_row = static_cast<int>(character->rows);
            }
        }
        max_row *= 2;
        SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, required_width, max_row);
        int x = 0;
        for (const auto c : text_) {
            const auto character = (font_->get_character(c)).get();
            const auto metrics = character->metrics;
            SDL_Rect dst_rect = {static_cast<int>(x + character->metrics.horiBearingX/64), static_cast<int>((max_row * 32 - metrics.horiBearingY)/64), static_cast<int>(metrics.width / 64), static_cast<int>(character->rows)};

            if (const auto error = SDL_UpdateTexture(texture, &dst_rect, character->bitmap.get(), character->pitch);
                error != 0) {
                //std::cerr << "Could not update texture: " << SDL_GetError() << std::endl;
            }
            x += (metrics.horiAdvance) / 64 ;

            //std::wcout << c << ": " << metrics.horiAdvance/64 << " " << x << std::endl;
        }
        SDL_FRect srcRect = {0, 0, static_cast<float>(required_width), static_cast<float>(max_row)};
        SDL_FRect dstRect = {static_cast<float>(x_), static_cast<float>(y_), static_cast<float>(required_width), static_cast<float>(max_row)};



        SDL_RenderTexture(renderer, texture, &srcRect, &dstRect);

    }
} // namespace squid
