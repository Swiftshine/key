#ifndef MSL_INT2TYPE_H
#define MSL_INT2TYPE_H

namespace Metrowerks {
    template <int I>
    struct int2type {
        enum { val = I };

        // int value; // assumed
    };
}

#endif