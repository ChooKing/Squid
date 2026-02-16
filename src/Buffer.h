#ifndef SQUID_BUFFER_H
#define SQUID_BUFFER_H

#include "globals.h"
#include <memory>

namespace squid {
    class Buffer {
        std::shared_ptr<unsigned char[]> pixels_{};
        int width_{0};
        int height_{0};
        int bytes_per_pixel_{BYTES_PER_PIXEL};
    public:
        Buffer() = default;
        Buffer(int width, int height, int bpp = BYTES_PER_PIXEL);
        Buffer(int width, int height, std::shared_ptr<unsigned char[]> pixels, int bpp = BYTES_PER_PIXEL);

        [[nodiscard]] int get_bpp() const;
        [[nodiscard]] int get_height() const;
        [[nodiscard]] int get_width() const;
        [[nodiscard]] std::shared_ptr<unsigned char[]> get_pixels();

        void blit(const Buffer& source, int x, int y) const;
    };
}



#endif // SQUID_BUFFER_H
