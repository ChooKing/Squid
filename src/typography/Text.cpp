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
    }

    void Text::measure_text() {
        const auto font_metrics = font_->font_metrics();
        const auto required_height =
                font_metrics.height / 64;
        int required_width = 0;

        for (const auto c: text_) {
            const auto character = font_->get_character(c);
            required_width += (character->metrics.horiAdvance) / 64;
        }
        required_width_ = required_width;
        required_height_ = required_height;
    }
    void Text::render_texture() {
        measure_text();
        buffer_ = Buffer(required_width_, required_height_);

        const auto font_metrics = font_->font_metrics();

        texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, required_width_,
                                     required_height_);
        int x = 0;
        for (const auto c: text_) {
            const auto character = (font_->get_character(c)).get();
            const auto buffer = character->buffer;
            const auto metrics = character->metrics;
            if (buffer.get_width() != 0) {
                buffer_.blit(character->buffer, static_cast<int>(x + character->metrics.horiBearingX / 64), static_cast<int>(font_metrics.ascender/64  - metrics.horiBearingY / 64));
            }
            x += (metrics.horiAdvance) / 64;
        }
        src_rect_ = {0, 0, static_cast<float>(required_width_), static_cast<float>(required_height_)};
        dst_rect_ = {static_cast<float>(x_), static_cast<float>(y_), static_cast<float>(required_width_),
                     static_cast<float>(required_height_)};

        const SDL_Rect dst_rect = {0, 0, static_cast<int>(required_width_), static_cast<int>(required_height_)};

        if (const auto error = SDL_UpdateTexture(texture_, &dst_rect, buffer_.get_pixels().get(),
                                           buffer_.get_width() * buffer_.get_bpp());
            error != 0) {
            std::cerr << "Could not update texture: " << SDL_GetError() << std::endl;
        }
    }
} // namespace squid
