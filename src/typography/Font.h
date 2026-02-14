#ifndef SQUID_FONT_H
#define SQUID_FONT_H
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "freetype/freetype.h"
#include <SDL3/SDL.h>

namespace squid {
    struct Character {
        FT_Glyph_Metrics metrics;
        int pitch;
        unsigned int rows;
        std::shared_ptr<unsigned char[]> bitmap;
    };
    class Font {
        static FT_Library library_;
        static std::once_flag library_init_flag_;
        FT_Face face_{};
        std::unordered_map<char32_t, std::shared_ptr<Character>> characters_{};
        void add_character(wchar_t ch);
    public:
        explicit Font(const std::string &path, int size);
        [[nodiscard]] std::shared_ptr<Character> get_character(char32_t ch);
        [[nodiscard]] int get_height() const;
    };
}


#endif // SQUID_FONT_H
