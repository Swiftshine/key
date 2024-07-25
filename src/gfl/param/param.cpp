#include <gfl/param/param ase.h>
#include <decomp/thunks.h>

// note to self, all of gfl::Param shares this tu

using namespace gfl;


const char debug_text_1 []= "bool %-20s= %s";
const char state_true   []= "true";
const char state_false  []= "false";
const char debug_text_2 []= "\t#%s\n";
const char* dummy = "123456789ABCDEF";
// const char* debug_text_3  = "str  %-20s= \"%s\""; // this is apparently part of the string pool, but for another param type
// there seems to be one additional char however

ParamBool::ParamBool(const char* newLabel) 
    : Param(newLabel)
{
    value = false;    
}



asm int ParamBool::vf8(void) {
    nofralloc
    b TRKInitializeSerialHandler
}

void ParamBool::vfC() { return; }

// gfl::ParamS32A dtor
extern "C" void fn_806515E4();

asm ParamBool::~ParamBool(void) {
    nofralloc 
    b fn_806515E4
}


void ParamBool::Print(gfl::Console* console, u32 count) {
    PrintRepeat(console, count);
    console->Print("bool %-20s= %s", label, (value) ? "true" : "false");
    console->Print("\t#%s\n", 0);
}
