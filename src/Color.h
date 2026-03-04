#ifndef SQUID_COLOR_H
#define SQUID_COLOR_H
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"

namespace squid {
    class Color {
        Uint8 r_;
        Uint8 g_;
        Uint8 b_;
        Uint8 a_;
    public:
        Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        [[nodiscard]] Uint8 r() const;
        [[nodiscard]] Uint8 g() const;
        [[nodiscard]] Uint8 b() const;
        [[nodiscard]] Uint8 a() const;
        static void set_draw_color(SDL_Renderer* renderer, const Color & color);
    };
}



#endif // SQUID_COLOR_H
