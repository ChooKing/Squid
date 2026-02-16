#include "Buffer.h"

#include <utility>
namespace squid {
    Buffer::Buffer(const int width, const int height, const int bpp) : width_(width), height_(height), bytes_per_pixel_(bpp) {
        pixels_ = std::shared_ptr<unsigned char[]>(new unsigned char[width * height * bpp], std::default_delete<unsigned char[]>());
    }
    Buffer::Buffer(const int width, const int height, std::shared_ptr<unsigned char[]> pixels, const int bpp): Buffer(width, height, bpp) {
        pixels_ = std::move(pixels);
    }
    int Buffer::get_bpp() const {
        return bytes_per_pixel_;
    }
    int Buffer::get_width() const {
        return width_;
    }
    int Buffer::get_height() const {
        return height_;
    }
    std::shared_ptr<unsigned char[]> Buffer::get_pixels() {
    return pixels_;
}
} // namespace squid
