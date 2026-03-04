#ifndef SQUID_SPAN_H
#define SQUID_SPAN_H
#include <string>
#include "../typography/Font.h"

namespace squid {
    class Span{
        //Different from HTML span. Holds no information other than Font and string
        //Spans do not hold any positional information or ability to render
        //Must be contained within an Inline container to be usable in UI
        std::shared_ptr<Font> font_;
        std::string text_;
    };
}



#endif // SQUID_SPAN_H
