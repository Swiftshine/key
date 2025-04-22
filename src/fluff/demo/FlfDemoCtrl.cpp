#include "demo/FlfDemoCtrl.h"


void FlfDemoCtrl::GetName(gfl::Pointer<StringCounter>& str, const char* name) {
    uint count = 0;

    str->mString = nullptr;

    for (char* c = (char*)name; *c != 0; c++) {
        if (*c == '_') {
            count++;
        }
    }

    str->mCounter = count;

    std::string nameString(name);

    str.Create(new (gfl::HeapID::Work) char[count * 2]);

    size_t nameLen = nameString.length();

    for (size_t i = 0; i < nameLen; i++) {
        if (nameString[i] == '_') {

        }
    }
}