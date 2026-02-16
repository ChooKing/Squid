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
    std::shared_ptr<unsigned char[]> Buffer::get_pixels() const{
    return pixels_;
}
    void Buffer::blit(const Buffer &source, int x, int y) const {
        const auto source_pixels = source.pixels_.get();
        for (auto row = 0; row < source.get_height(); ++row) {
            memcpy(this->pixels_.get() + ((row + y) * this->width_ + x) * this->bytes_per_pixel_, source_pixels + row * source.width_ * source.bytes_per_pixel_, source.get_width() * source.get_bpp());
        }
    }
} // namespace squid
