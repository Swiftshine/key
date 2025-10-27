#ifndef GFL_PARAMREADER_H
#define GFL_PARAMREADER_H

#include <string>
#include "gflFixedMemoryStream.h"
#include "gflParam.h"

namespace gfl {

class ParamReader {
public:
    /* Structures */

    ENUM_CLASS(TokenType,
        End             = -1,
        Invalid         = 0,
        LeftBrace       = 1,
        RightBrace      = 2,
        LeftParen       = 3,
        RightParen      = 4,
        LeftBracket     = 5,
        RightBracket    = 6,
        Comma           = 7,
        Assignment      = 8,
        Minus           = 9,
        TypeS32         = 10, // the data type "s32"
        TypeF32         = 11, // the data type "f32"
        TypeString      = 12, // the data type "str"
        TypeBool        = 13, // the data type "bool"
        ValueS32        = 14, // the value of an s32
        ValueF32        = 15, // the value of an f32
        ValueTrue       = 16, // the value "true"
        ValueFalse      = 17, // the value "false"
        Identifier      = 18, // the parameter name
        ValueString     = 19, // the value of a string
        Description     = 20, // the parameter description (indicated by a '#')
    );


    /* Constructor + Destructor */
    ParamReader();
    ~ParamReader();

    /* Class Methods */
    int GetTokenType();
    const char* GetTokenString(int tokenType);
    void fn_80652EC8();
    void fn_80653124();
    Param* GetNextParam(ParamGroup* pParamGroup);
    ParamGroup* GetParamGroup(ParamGroup* pParamGroup);
    ParamS32* GetParamS32(ParamGroup* pParamGroup);
    ParamF32* GetParamF32(ParamGroup* pParamGroup);
    ParamStr* GetParamStr(ParamGroup* pParamGroup);
    ParamBool* GetParamBool(ParamGroup* pParamGroup);
    ParamS32A* GetParamS32A(ParamGroup* pParamGroup);
    ParamF32A* GetParamF32A(ParamGroup* pParamGroup);
    ParamStrA* GetParamStrA(ParamGroup* pParamGroup);
    ParamBoolA* GetParamBoolA(ParamGroup* pParamGroup);

    /* Class Members */

    /* 0x000 */ FixedMemoryStream* mFixedMemoryStream;
    /* 0x004 */ union {
        int mInt;
        float mFloat;
        double mDouble;
    } mCurrentValue;
    /* 0x00C */ char mParamGroupName[512];
    /* 0x20C */ size_t mParamGroupNameLength;
    /* 0x210 */ char mBuffer[512];
    /* 0x410 */ size_t mBufferSize;
    /* 0x414 */ size_t mBufferSeekPosition;
    /* 0x418 */ int mLastReadCharacter; // specifically an int, not a char
    /* 0x41C */ char mCurrentLineContents[512];
    /* 0x61C */ size_t mCurrentColumn; // refers to the file
    /* 0x620 */ size_t mCurrentLineNumber; // refers to the file
    /* 0x624 */ std::string mFilename;
    /* 0x630 */ bool m_630;
    /* 0x634 */ int mCurrentTokenType;
};

}

#endif