#include <gfl/task/Task.h>
#include <gfl/mem/Mem.h>
#include <gfl/task/TaskInfo.h>
#include <decomp/thunks.h>

const char gfl::Task::DeathMarker[] = "@Z";
const char gfl::Task::NoName[] = "NONAME";
const char gfl::Task::AllocError[] = "Memory allocation error";

gfl::Task::Task() { }

void gfl::Task::Init(const char* newName) {
    TaskList* list = TaskList::Instance;
    int i = 0;
    TaskInfo* tinfo;
    
    for (i; i < TASK_COUNT; i++) {
        if (!list->active[i]) {
            tinfo = &list->taskInfo[i];
            list->taskInfo[i].parent = NULL;
            list->taskInfo[i].sibling = NULL;
            list->taskInfo[i].child = NULL;
            list->taskInfo[i].owner = NULL;
            list->taskInfo[i].flags = 0;
            memset(tinfo, 0, 0x17);
            list->active[i] = true;
            goto exit_loop;
        }
    }
    
    tinfo = NULL;
exit_loop:
    this->info = tinfo;

    if (newName) {
        gfl::mem::Memcpy(tinfo->name, 0x17, const_cast<char*>(newName));
    } else {
        gfl::mem::Memcpy(tinfo->name, 0x17, const_cast<char*>(NoName));
    }

    tinfo->owner = this;
    tinfo->flags = 0xF1;
    tinfo->parent = NULL;
    tinfo->sibling = NULL;
    tinfo->child = NULL;
}

gfl::Task::~Task() { }



u32 gfl::Task::PollTask() {
    TaskInfo* myTaskInfo = this->info;
    Task* childTask;
    
    // if the task is about to execute and it has the means to do so, it will
    if (!(this->_10 & ~this->_14) && this->functorFunc) {
        TaskInfo::SetCurrentTask(this);
        this->functorFunc->operator()();
        TaskInfo::ClearCurrentTask();

        // after executing, check the task's information to see if the task still exists
        if (!myTaskInfo->owner) {
            // if it doesn't, it was destroyed and has successfully completed its task
            return Task::Status::TaskExecuted;
        }
        // if it does, there are child tasks that must be executed as well
    }

    // so get the next child
    childTask = TaskInfo::GetNextChild(this->info);
    
    while (childTask) {
        TaskInfo* childTaskInfo = childTask->info;
        u32 x = childTask->PollTask();
        if (!myTaskInfo->owner) {
            return Task::Status::ChildrenExecuted;
        }

        if (x - 1 > 1) {
            if (x == Task::Status::StillProcessing) {
                childTask = TaskInfo::GetNextSibling(childTask->info->sibling);
            }
        }
        else {
            childTask = TaskInfo::GetNextSibling(childTaskInfo->sibling);
        }
    }

    return Task::Status::StillProcessing;
}

void gfl::Task::MakeChild(Task* newChild) {
    TaskInfo* newChildInfo = newChild->info;
    TaskInfo* thisInfo = this->info;
    TaskInfo* curChildInfo;
    TaskInfo* c;
    TaskInfo* newSiblingInfo;

    u8 newChildFlags = newChildInfo->flags;
    // we are the new child's parent, but we need to check if we currently have a child
    newChildInfo->parent = thisInfo;
    curChildInfo  = thisInfo->child;

    if (!curChildInfo) {
        // if we don't have a child, we can simply adopt the new one
        thisInfo->child = newChildInfo;
        return;
    }

    if (newChildFlags == 0xF0) {
        // if we already have a child, it becomes a sibling
        thisInfo->child = newChildInfo;
        newChildInfo->sibling = curChildInfo;
        newChildInfo->flags = 0xF0;
        return;
    }

    if (newChildFlags == 0xF1) {
        do {
            c = curChildInfo;
            curChildInfo = c->sibling;
        } while (c->sibling);
        c->sibling = newChildInfo;
        newChildInfo->flags = 0XF1;
        return;
    }

    newSiblingInfo = NULL; // ghidra's output might be tweaking, why tf would you make a pointer NULL before using it
    // ghidra's output is DEFINITELY tweaking, why tf would you not have a valid pointer at all before using it

    while (true) {
        if (!curChildInfo) {
            newSiblingInfo->sibling = newChildInfo;
            newChildInfo->flags = newChildFlags;
            return;
        }

        if (newChildFlags < curChildInfo->flags) break;

        newSiblingInfo = curChildInfo;
        curChildInfo = curChildInfo->sibling;
    }

    if (!newSiblingInfo) {
        thisInfo->child = newChildInfo;
        newChildInfo->sibling = curChildInfo;
    } else {
        newSiblingInfo->sibling = newChildInfo;
        newChildInfo->sibling = curChildInfo;
    }
    newChildInfo->flags = newChildFlags;
}

void gfl::Task::Replace(gfl::Task* other) {
    TaskInfo *inf;
    TaskInfo *theirTaskInfo;
    TaskInfo *myChildInfo;
    
    inf = info;
    theirTaskInfo = other->info;
    myChildInfo = inf->child;
    if (myChildInfo == theirTaskInfo) {
        theirTaskInfo->parent = NULL;
        inf->child = theirTaskInfo->sibling;
        theirTaskInfo->sibling = NULL;
        return;
    } 

    for (inf = myChildInfo->sibling; myChildInfo; inf = inf->sibling){
        if (inf == theirTaskInfo) {
            theirTaskInfo->parent = NULL;
            myChildInfo->sibling = theirTaskInfo->sibling;
            theirTaskInfo->sibling = NULL;
            return;
        }
        myChildInfo = inf;
    }
}

gfl::Task* gfl::Task::GetNextChild() {
    return TaskInfo::GetNextChild(this->info);
}

gfl::Task* gfl::Task::GetNextSibling() {
    return TaskInfo::GetNextSibling(this->info->sibling);
}
void gfl::Task::SetFlags(u8 newFlags) {
    info->flags = newFlags;
}

u8 gfl::Task::GetFlags() {
    return info->flags;
}

gfl::Task* gfl::Task::GetParent() {
    return TaskInfo::GetParent(this->info);
}

void gfl::Task::SetTaskName(const char* newName) {
    char* dest = info->name;

    if (newName) {
        gfl::mem::Memcpy(dest, TASK_NAME_LENGTH, const_cast<char*>(newName));
        return;
    }

    gfl::mem::Memcpy(dest, TASK_NAME_LENGTH, const_cast<char*>(NoName));
}

void gfl::Task::CreateSubtask(u8 groupID) {
    // incomplete
    TaskInfo* parentInfo = this->info->parent;
    Task* parentTask;
    Subtask* sub;
    if (!parentInfo) {
        parentTask = NULL;
    } else {
        parentTask = parentInfo->owner;
    }

    u32 groupU32 = static_cast<u32>(groupID);

    sub = new Subtask;
    
    if (!sub) {
        fprintf(stderr, AllocError);
        abort();
    }

    if (!&sub->_8) {
        sub->_8 = 2;
        sub->parent = parentTask;
        sub->owner = this;
        sub->groupID = groupU32;
    }
}

