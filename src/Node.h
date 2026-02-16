#ifndef SQUID_NODE_H
#define SQUID_NODE_H

namespace squid {
    class Node {
    protected:
        int required_width_ = 0;
        int required_height_ = 0;
        virtual void measure() = 0;
    public:
        virtual ~Node() = default;
    };

}
#endif // SQUID_NODE_H
