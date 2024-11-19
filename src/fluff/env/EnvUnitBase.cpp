#include "env/EnvUnitBase.h"

using namespace env;

EnvUnitBase::EnvUnitBase(gfl::Task* parent, const char* taskName, uint arg3) 
    : EnvObject(parent, 0, taskName, arg3)
{ }

// not complete -- fix std::dequeue dtor
EnvUnitBase::~EnvUnitBase() {}
