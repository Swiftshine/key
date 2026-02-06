// #include "util/NURBSOption.h"
// #include <string>

// // https://decomp.me/scratch/8ylQ9
// NURBSOption::NURBSOption(const char* pName)
//     : mArray(nullptr)
// {
//     size_t count = 0;

//     for (const char* c = pName; *c != 0; c++) {
//         if (*c == '_') {
//             count++;
//         }
//     }

//     mCount = count;
//     mArray.Create(count * 2);

//     std::string nameString = pName;

//     size_t nameLen = nameString.length();
//     size_t pos = 0;
//     size_t index = 0;

//     for (size_t i = 0; i < nameLen; i++) {
//         if (nameString[i] == '_') {
//             std::string tempStr(nameString, pos, i - pos);
//             mArray[index] = atoi(tempStr.c_str());
//             pos++;
//         } else if (nameString[i] == '|') {
//             std::string tempStr(nameString, pos, i - pos);
//             mArray[index + 1] = atoi(tempStr.c_str());
//             pos++;
//             index += 2;
//         }
//     }
// }

// NURBSOption::~NURBSOption() { }

// // https://decomp.me/scratch/WL2Uc
// s16 NURBSOption::GetOption(float arg0) {
//     s16 result;

//     if (mCount == 0) {
//         result = 0;
//     } else {
//         u16* arr = mArray;
//         if (static_cast<float>(*arr) <= arg0) {
//             int i = mCount;
//             result = 0;

//             while (i != 0) {
//                 if (
//                     static_cast<float>(*arr) <= arg0 &&
//                     arg0 < static_cast<float>(arr[(result + 1) * 2])
//                 ) {
//                     return arr[result * 2 + 1];
//                 }

//                 arr += 2;
//                 result++;
//                 i--;
//             }

//             result = arr[(mCount - 1) * 2 + 1];
//         } else {
//             result = arr[1];
//         }
//     }

//     return result;
// }
