#ifndef HOMEBUTTON_GROUPANMCONTROLLER_H
#define HOMEBUTTON_GROUPANMCONTROLLER_H

#include "types.h"

namespace homebutton {
    class GroupAnmController {
    public:
        GroupAnmController();
        ~GroupAnmController();


        virtual void fn_806FF870();
    public:
        uint m_4;
        uint m_8;
        uint m_C;
        uint m_10;
        uint m_14;
        uint m_18;
        uint m_1C;
        void* m_20;
        void* m_24;
    };
}

#endif