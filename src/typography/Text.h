#ifndef SQUID_TEXT_H
#define SQUID_TEXT_H
#include <memory>
#include <string>

#include "Font.h"

namespace squid {
    class Text {
        std::wstring text_;
        std::shared_ptr<Font> font_;
        //Coordinates are actually offsets relative to the window or other element
        int x_ = 0;
        int y_ = 0;
    public:
        Text(std::wstring text, const std::shared_ptr<Font> &font);
        void draw(SDL_Renderer* renderer) const;
    };
}

#endif // SQUID_TEXT_H
