#include "Text.h"

#include <iostream>
#include <ostream>
#include <utility>
namespace squid {
    Text::Text(std::wstring text, const std::shared_ptr<Font> &font, SDL_Renderer *renderer) :
        text_(std::move(text)), font_(font), renderer_(renderer) {
        render_texture();
    }
    void Text::draw() const {
        SDL_RenderTexture(renderer_, texture_, &src_rect_, &dst_rect_);
        SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
        const SDL_FRect diag_rect = {dst_rect_.x, dst_rect_.y, dst_rect_.w, dst_rect_.h};
        SDL_RenderRect(renderer_, &diag_rect);
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    }

    void Text::render_texture() {
        const auto font_metrics = font_->font_metrics();
        const auto required_height =
                font_metrics.height / 64 + 16; // The reason for the extra 16 is not known but determined via testing.
        int required_width = 0;

        int test_height = 0;

        for (const auto c: text_) {
            const auto character = font_->get_character(c);
            required_width += (character->metrics.horiAdvance) / 64;


        }

        texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, required_width,
                                     required_height);
        int x = 0;
        for (const auto c: text_) {
            const auto character = (font_->get_character(c)).get();
            const auto metrics = character->metrics;
            if (character->pitch != 0) {
                SDL_Rect dst_rect = {static_cast<int>(x + character->metrics.horiBearingX / 64),
                                     static_cast<int>(font_metrics.ascender/64  - metrics.horiBearingY / 64),
                                     (character->pitch / 4), static_cast<int>(character->rows)};

                if (const auto error =
                            SDL_UpdateTexture(texture_, &dst_rect, character->bitmap.get(), character->pitch);
                    error != 0) {
                    std::cerr << "Could not update texture: " << SDL_GetError() << std::endl;
                }
            }
            x += (metrics.horiAdvance) / 64;
        }
        src_rect_ = {0, 0, static_cast<float>(required_width), static_cast<float>(required_height)};
        dst_rect_ = {static_cast<float>(x_), static_cast<float>(y_), static_cast<float>(required_width),
                     static_cast<float>(required_height)};
    }
} // namespace squid
