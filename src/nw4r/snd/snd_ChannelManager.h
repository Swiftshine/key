#ifndef NW4R_SND_CHANNEL_MANAGER_H
#define NW4R_SND_CHANNEL_MANAGER_H
#include "nw4r/types_nw4r.h"

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            struct ChannelManager
            {
                static ChannelManager * GetInstance();

                void UpdateAllChannel();
            };
        }
    }
}

#endif