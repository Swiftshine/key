#include "env/EnvUnitBase.h"

using namespace env;

EnvUnitBase::EnvUnitBase(gfl::Task* pParentTask, const char* pTaskName, u32 arg3) 
    : EnvObject(pParentTask, 0, pTaskName, arg3)
{ }

// not complete -- fix std::deque dtor
EnvUnitBase::~EnvUnitBase() {}
