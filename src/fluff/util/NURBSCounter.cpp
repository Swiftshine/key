#include "util/NURBSCounter.h"
#include <string>

// https://decomp.me/scratch/8ylQ9
NURBSCounter::NURBSCounter(const char* name)
    : mArray(nullptr)
{
    size_t count = 0;

    for (const char* c = name; *c != 0; c++) {
        if (*c == '_') {
            count++;
        }
    }

    mCount = count;
    mArray.Create(count * 2);

    std::string nameString = name;

    size_t nameLen = nameString.length();
    size_t pos = 0;
    size_t index = 0;

    for (size_t i = 0; i < nameLen; i++) {
        if (nameString[i] == '_') {
            std::string tempStr(nameString, pos, i - pos);
            mArray[index] = atoi(tempStr.c_str());
            pos++;
        } else if (nameString[i] == '|') {
            std::string tempStr(nameString, pos, i - pos);
            mArray[index + 1] = atoi(tempStr.c_str());
            pos++;
            index += 2; 
        }
    }
}

NURBSCounter::~NURBSCounter() { }