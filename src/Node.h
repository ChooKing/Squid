#ifndef SQUID_NODE_H
#define SQUID_NODE_H

namespace squid {
    struct Dimensions {
        int width{};
        int height{};
    };
    struct InlineDimensions : Dimensions {
        int start_x{};
        int end_x{};
    };
    class Node {
    protected:
        //Required measurements are for space needed to fit contents.
        //This may differ from rendered or requested sizes.
        int required_width_ = 0;
        int required_height_ = 0;
        virtual void measure(int requested_width, int requested_height) = 0;
    public:
        virtual ~Node() = default;
        [[nodiscard]] virtual Dimensions get_dimensions() const = 0;
    };

}
#endif // SQUID_NODE_H
