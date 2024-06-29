#include <gfl/task.h>
#include <gfl/mem.h>

gfl::Task::Task() { }

gfl::Task::Task(const char* newName) {
    gfl::Task::Info* t_info;

    static bool* enabled = &gfl::TaskList::enabled[0];

    if (!*enabled) {
        for (u32 i = 0; i < 1400; i++) {
            gfl::Task::Info* inf = &gfl::TaskList::taskInfo[i];
            inf->child1 = NULL;
            inf->child2 = NULL;
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
        gfl::mem::memcpy(t_info->name, 0x17, "NONAME");
    } else {
        gfl::mem::memcpy(t_info->name, 0x17, (char*)newName);
    }

    info = t_info;

    info->owner  = this;
    info->flags  = 0xF1;
    info->child1 = NULL;
    info->child2 = NULL;
    info->_20    = 0;
}

gfl::Task::~Task() { }

void gfl::Task::SetFlags(u8 newFlags) {
    info->flags = newFlags;
}

u8 gfl::Task::GetFlags() {
    return info->flags;
}

gfl::Task::Info* gfl::Task::GetLeaf() {
    // unfinished
    return NULL;
}
