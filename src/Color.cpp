#include "Color.h"
namespace squid {
    Color::Color(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a): r_(r), g_(g), b_(b), a_(a) {}
    Uint8 Color::r() const {
        return r_;
    }
    Uint8 Color::g() const {
        return g_;
    }
    Uint8 Color::b() const {
        return b_;
    }
    Uint8 Color::a() const {
        return a_;
    }
    void Color::set_draw_color(SDL_Renderer *renderer, const Color & color) {
        SDL_SetRenderDrawColor(renderer, color.r_, color.g_, color.b_, color.a_);
    }

} // namespace squid
