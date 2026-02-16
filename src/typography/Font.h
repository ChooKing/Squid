#ifndef SQUID_FONT_H
#define SQUID_FONT_H
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "freetype/freetype.h"
#include "../Buffer.h"

namespace squid {
    struct Character {
        FT_Glyph_Metrics metrics{};
        unsigned int rows{};
        Buffer buffer;
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
        [[nodiscard]] FT_Size_Metrics font_metrics() const;
    };
}


#endif // SQUID_FONT_H
