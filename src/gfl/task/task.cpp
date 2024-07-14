#include <gfl/task/task.h>
#include <gfl/mem.h>
#include <gfl/task/taskinfo.h>
gfl::Task::Task() { }

void gfl::Task::Init(const char* newName) {
    gfl::TaskInfo* t_info;

    static bool* enabled = &gfl::TaskList::Instance->active[0];

    if (!*enabled) {
        for (u32 i = 0; i < 1400; i++) {
            gfl::TaskInfo* inf = &gfl::TaskList::Instance->taskInfo[i];
            inf->_18 = NULL;
            inf->_1C = NULL;
            inf->_20 = 0;
            inf->owner = NULL;
            inf->flags = 0;
            memset(inf, '\0', 0x17);
            *enabled = true;
            goto LAB_806458c4;
        }
        enabled++;
    }

LAB_806458c4:
    if (!newName) {
        gfl::mem::Memcpy(t_info->name, 0x17, "NONAME");
    } else {
        gfl::mem::Memcpy(t_info->name, 0x17, const_cast<char*>(newName));
    }

    info = t_info;

    info->owner  = this;
    info->flags  = 0xF1;
    info->_18 = NULL;
    info->_1C = NULL;
    info->_20    = 0;
}

gfl::Task::~Task() { }

void gfl::Task::SetFlags(u8 newFlags) {
    info->flags = newFlags;
}

u8 gfl::Task::GetFlags() {
    return info->flags;
}
