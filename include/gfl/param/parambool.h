#ifndef GFL_PARAM_BOOL_H
#define GFL_PARAM_BOOL_H

#include <gfl/param/parambase.h>

namespace gfl {
    class ParamBool : public Param {
    public:
        ParamBool(const char* newLabel);
        virtual int  vf8();
        virtual void vfC();
        virtual ~ParamBool();
        virtual void Print(gfl::Console* console, u32 count);
    public:
        bool value;
        /* implicit padding */
        const char* type; /* BasicString* ? */
    };

    ASSERT_SIZE(ParamBool, 0x30)
}

#endif
