#include "Text.h"

#include <iostream>
#include <ostream>
#include <utility>
namespace squid {
    Text::Text(std::wstring text, const std::shared_ptr<Font> &font, SDL_Renderer *renderer) :
        text_(std::move(text)), font_(font), renderer_(renderer) {
        render();
    }
    Buffer Text::get_buffer() const { return buffer_; }
    Dimensions Text::get_dimensions() const { return Dimensions{measure_result_.width, measure_result_.height}; }
    void Text::set_indent(const int indent) {
        indent_ = indent;
        render();
    }
    void Text::set_dimensions(const int width, const int height) {
        required_width_ = width;
        required_height_ = height;
    }

    void Text::measure(const int requested_width, const int requested_height) {
        measure_inline(requested_width, requested_height, indent_);
    }
    void Text::measure_inline(const int requested_width, const int requested_height, const int indent) {
        TextMeasure measure;
        if (requested_width != -1 && requested_height != -1) {
            measure.width = requested_width;
            measure.height = requested_height;
            return;
        }
        const auto font_metrics = font_->font_metrics();
        int last_end_pos = 0;
        int end_pos = 0;
        int pos = 0;
        int current_line_width = indent;
        int max_width = 0;
        int measured_height = text_.empty() ? 0 : font_metrics.height / 64;
        while (pos < text_.size()) {
            const auto ch = text_[pos];
            const auto character = font_->get_character(ch);
            const auto char_width = (character->metrics.horiAdvance) / 64;
            if (ch == ' ' || ch == '\t') {
                end_pos = pos - 1;
            }
            if (ch == '\n') {
                measured_height += font_metrics.height / 64;
                if (requested_height != -1 && measured_height > requested_height) {
                    measure.width = max_width;
                    measure.height = requested_height;
                    return;
                }
                current_line_width = 0;
                end_pos = 0;
            } else if (requested_width != -1 && (current_line_width + char_width > requested_width)) {
                measured_height += font_metrics.height / 64;
                if ((requested_height != -1) && (measured_height > requested_height)) {
                    measure.width = max_width;
                    measure.height = requested_height;
                    return;
                }
                current_line_width = 0;
                measure.line_characters.push_back(end_pos - last_end_pos + 1);
                last_end_pos = end_pos + 1;
                pos = end_pos;
                end_pos = 0;
            } else {
                current_line_width += char_width;
                if (current_line_width > max_width) {
                    max_width = current_line_width;
                }
            }
            pos++;
        }
        measure.line_characters.push_back(pos - last_end_pos);
        measure.width = max_width;
        measure.height = measured_height;
        measure_result_ = measure;
    }
    void Text::render() {
        measure(300, -1);
        required_width_ = measure_result_.width;
        required_height_ = measure_result_.height;
        buffer_ = Buffer(required_width_, required_height_);

        int pos = 0;
        int x = indent_;
        int y = 0;
        const auto font_metrics = font_->font_metrics();
        for (const int line_character: measure_result_.line_characters) {
            for (auto i = 0; i < line_character; ++i) {
                const auto c = text_[pos];
                if (i == 0 && c == ' ') {
                    pos++;
                    continue;
                };
                const auto character = (font_->get_character(c)).get();
                const auto buffer = character->buffer;
                const auto metrics = character->metrics;
                const auto char_width = (character->metrics.horiAdvance) / 64;
                if (buffer.get_width() != 0) {
                    buffer_.blit(character->buffer, static_cast<int>(x + character->metrics.horiBearingX / 64),
                                 y + static_cast<int>(font_metrics.ascender / 64 - metrics.horiBearingY / 64));
                }
                x += char_width;
                pos += 1;
            }
            x = 0;
            y += font_metrics.height / 64;
        }

        src_rect_ = {0, 0, static_cast<float>(required_width_), static_cast<float>(required_height_)};
        dst_rect_ = {static_cast<float>(x_), static_cast<float>(y_), static_cast<float>(required_width_),
                     static_cast<float>(required_height_)};
    }
} // namespace squid