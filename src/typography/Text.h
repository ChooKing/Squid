#ifndef SQUID_TEXT_H
#define SQUID_TEXT_H
#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <vector>
#include "../Node.h"
#include "Font.h"

namespace squid {
    struct TextMeasure {
        int width;
        int height;
        std::vector<int> line_characters;
    };
    class Text: Node {
        std::wstring text_;
        std::shared_ptr<Font> font_;
        SDL_Renderer* renderer_ = nullptr;
        Buffer buffer_;
        //Coordinates are actually offsets relative to the window or other element
        int x_ = 0;
        int y_ = 0;
        int indent_ = 0;
        TextMeasure measure_result_;
        //int measured_width_ = 0;
        //int measured_height_ = 0;
        SDL_FRect src_rect_ = {0, 0, 0, 0};
        SDL_FRect dst_rect_ = {0, 0, 0, 0};
        void measure(int requested_width, int requested_height) override;
        void measure_inline(int requested_width, int requested_height, int indent);
        void render();
    public:
        Text(std::wstring text, const std::shared_ptr<Font> &font, SDL_Renderer* renderer);
        [[nodiscard]] Buffer get_buffer() const;
        [[nodiscard]] Dimensions get_dimensions() const override;
        void set_indent(int indent);
        void set_dimensions(int width, int height);

    };
}

#endif // SQUID_TEXT_H
