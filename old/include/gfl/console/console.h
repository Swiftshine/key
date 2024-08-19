#ifndef GFL_CONSOLE_H
#define GFL_CONSOLE_H

namespace gfl {
    class Console {
    public:
        virtual void dummy();

        void Print(const char* msg, ...);
    };
}

#endif
