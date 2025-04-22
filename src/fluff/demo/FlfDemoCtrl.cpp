#include "demo/FlfDemoCtrl.h"

// https://decomp.me/scratch/YdGGn
void FlfDemoCtrl::GetCount(gfl::CountedArray<u16>* dst, const char* name) {
    size_t count = 0;

    dst->Set(nullptr);

    for (const char* c = name; *c != 0; c++) {
        if (*c == '_') {
            count++;
        }
    }

    dst->SetCount(count);

    dst->Create(new (gfl::HeapID::Work) u16[count * 2]);

    std::string nameString = name;

    size_t nameLen = nameString.length();
    size_t pos = 0;
    size_t index = 0;

    for (size_t i = 0; i < nameLen; i++) {
        if (nameString[i] == '_') {
            std::string tempStr(nameString, pos, i - pos);
            dst->Get()[index] = atoi(tempStr.c_str());
            // pos = i + 1;
            pos++;
        } else if (nameString[i] == '|'){
            std::string tempStr(nameString, pos, i - pos);
            dst->Get()[index + 1] = atoi(tempStr.c_str());
            // pos = i + 1;
            pos++;
            index += 2;
        }
    }
}
