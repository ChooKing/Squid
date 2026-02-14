#include "Font.h"

#include <cstring>
#include <iostream>
#include <ostream>
#include <stdexcept>

#include "freetype/ftbitmap.h"

namespace squid {
    FT_Library Font::library_ = nullptr;
    std::once_flag Font::library_init_flag_;

    Font::Font(const std::string &path, const int size) {
        std::call_once(library_init_flag_, []() {
            if (FT_Init_FreeType(&library_) != 0) {
                throw std::runtime_error("Could not initialize FreeType library");
            }
        });
        if (const auto error = FT_New_Face(library_, path.c_str(), 0, &face_); error != 0) {
            std::cerr << "Could not load font: " << FT_Error_String(error) << std::endl;
        }

        if (const auto error = FT_Set_Pixel_Sizes(face_, 0, size); error != 0) {
            std::cerr << "Could not set pixel size: " << FT_Error_String(error) << std::endl;
        }

        for (auto ch = U'!'; ch < U'~'; ++ch) {
            add_character(ch);
        }
    }

    void Font::add_character(wchar_t ch) {
        if (FT_Load_Char(face_, ch, FT_LOAD_RENDER) != 0) {
            std::cerr << "Could not load character" << std::endl;
        } else {
            constexpr int bytes_per_pixel = 4;
            const FT_Bitmap bitmap = face_->glyph->bitmap;
            int width = bitmap.width;
            if (width % 4 != 0) {
                width += 4 - (width % 4);
            }
            const std::size_t size = static_cast<std::size_t>(bitmap.rows) *
                                     width * bytes_per_pixel;
            const auto shared_copy =
                    std::shared_ptr<unsigned char[]>(new unsigned char[size], std::default_delete<unsigned char[]>());
            for (auto row = 0; row < bitmap.rows; ++row) {
                for (auto col = 0; col < bitmap.width; ++col) {
                    const auto pos = (row * width + col) * bytes_per_pixel;
                    shared_copy[pos] = 255;
                    shared_copy[pos + 1] = 255;
                    shared_copy[pos + 2] = 255;
                    shared_copy[pos + 3] = bitmap.buffer[row * bitmap.pitch + col];
                }
            }
            Character character = {face_->glyph->metrics, width * bytes_per_pixel, bitmap.rows,
                                   shared_copy};
            characters_.emplace(ch, std::make_shared<Character>(character));
        }
    }
    std::shared_ptr<Character> Font::get_character(const char32_t ch) {
        if (const auto character = characters_.find(ch); character == characters_.end()) {
            add_character(ch);
        }
        return characters_.at(ch);
    }
    int Font::get_height() const {
        return (face_->size->metrics.ascender - face_->size->metrics.descender) >> 6;
    }
} // namespace squid
