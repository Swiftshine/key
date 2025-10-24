#include "gflParam.h"
using namespace gfl;

ParamS32::ParamS32(const char* pLabel)
    : Param(pLabel)
    , mValue(0)
{ }

ParamS32::~ParamS32() { }

int ParamS32::vf8() {
    return 0;
}

__declspec(no_linker_opts) void ParamS32::vfC() { }

__declspec(no_linker_opts) void ParamS32::Print(Console* pConsole, uint numTabs) { }