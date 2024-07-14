
#include <gfl/mem.h>
#include <decomp/thunks.h>
#include <gfl/task/taskinfo.h>

gfl::TaskList* gfl::TaskList::Instance;
gfl::Task* gfl::TaskList::CurrentTask;

inline gfl::TaskList::TaskList() { memset(this->active, false, TASK_COUNT); }
inline gfl::TaskList::~TaskList() { }


void gfl::TaskList::MakeInstance() {
    TaskList::Instance = new (gfl::mem::HeapID::LIB1) TaskList;
}

gfl::TaskInfo::TaskInfo() {
    flags = 0;
    _18 = NULL;
    _1C = NULL;
    _20 = NULL;
    owner = NULL;
    memset(name, 0, sizeof(name));
}

asm gfl::TaskInfo::~TaskInfo(void) {
    // this is necessary until i can figure out how to properly handle code merging
    // it's also possible that it's not code merging and was inline assembly to begin with
    nofralloc
    b common_dtor
}

void gfl::TaskList::RemoveInstance() {
    delete TaskList::Instance;
    TaskList::Instance = NULL;
    TaskList::ClearCurrentTask();
}

