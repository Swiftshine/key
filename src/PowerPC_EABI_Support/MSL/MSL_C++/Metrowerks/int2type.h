namespace Metrowerks {
    template <int I>
    struct int2type {
        enum { val = I };

        int value; // assumed
    };
}
