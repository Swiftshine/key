#ifndef GFL_PARAMREADER_H
#define GFL_PARAMREADER_H

#include <string>
#include "gflFixedMemoryStream.h"
#include "gflParam.h"

namespace gfl {

class ParamReader {
public:
    // required to use because the std::string destructor is both
    // non-inline and non-matching
    struct String {
        String()
            : m_0(0)
            , m_4(0)
            , mString(nullptr)
        { }

        ~String() {
            if ((m_0 >> 31)) {
                delete mString;
            }
        }

        std::string& ToString() {
            return *reinterpret_cast<std::string*>(this);
        }

        s32 m_0;
        s32 m_4;
        const char* mString;

    };

    /* Structures */

    enum TokenType {
        eTokenType_End             = -1,
        eTokenType_Invalid         = 0,
        eTokenType_LeftBrace       = 1, // {
        eTokenType_RightBrace      = 2, // }
        eTokenType_LeftParen       = 3, // (
        eTokenType_RightParen      = 4, // )
        eTokenType_LeftBracket     = 5, // [
        eTokenType_RightBracket    = 6, // ]
        eTokenType_Comma           = 7, // ,
        eTokenType_Assignment      = 8, // =
        eTokenType_Minus           = 9, // -
        eTokenType_TypeS32         = 10, // the data type "s32"
        eTokenType_TypeF32         = 11, // the data type "f32"
        eTokenType_TypeString      = 12, // the data type "str"
        eTokenType_TypeBool        = 13, // the data type "bool"
        eTokenType_ValueS32        = 14, // the value of an s32
        eTokenType_ValueF32        = 15, // the value of an f32
        eTokenType_ValueTrue       = 16, // the value "true"
        eTokenType_ValueFalse      = 17, // the value "false"
        eTokenType_Identifier      = 18, // the parameter name
        eTokenType_ValueString     = 19, // the value of a string
        eTokenType_Description     = 20, // the parameter description (indicated by a '#')
    };



    ParamReader(FixedMemoryStream* pMemoryStream);
    ~ParamReader();

    /* Class Methods */
    /// @return a `TokenType`.
    s32 ParseToken();
    const char* GetTokenString(s32 tokenType);
    void fn_80652EC8();
    void Reset(s32 unused = 1) DONT_INLINE_CLASS;
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

    // the below inline functions are not inline in YWW

    inline bool Read() {
        size_t len = mFixedMemoryStream->Read(mBuffer, sizeof(mBuffer));

        mBufferLength = len;
        if (len == 0) {
            return false;
        }

        mBufferSeekPosition = 0;
        return true;
    }

    inline s32 ReadCharacter() {
        if (mBufferSeekPosition == mBufferLength) {
            if (!Read()) {
                return -1;
            }
        }

        u8 chr = mBuffer[mBufferSeekPosition];
        mBufferSeekPosition++;
        mCurrentLineContents[mCurrentColumn] = chr;
        mCurrentColumn++;

        return chr;
    }


    bool IsAlphabetic(s32 character) {
        if (character - 'A' < 26 || character - 'a' < 26) {
            return true;
        }

        return false;
    }

    bool IsNumeric(s32 character) {
        if (character - '0' <= 9 || character == '.') {
            return true;
        }

        return false;
    }

    bool IsNewline(s32 character) {
        if (character == '\r' || character == '\n') {
            return true;
        }

        return false;
    }

    bool IsWhitespace(s32 character) {
        if (character == ' ' || character == '\t') {
            return true;
        }

        return false;
    }


    void UpdateWorkingBuffer(char byte) {
        mWorkingBuffer[mWorkingBufferLength++] = byte;
    }

    /* Class Members */

    /* 0x000 */ FixedMemoryStream* mFixedMemoryStream;
    /* 0x004 */ s32 mIntValue;
    /* 0x008 */ f32 mFloatValue;
    /* 0x00C */ char mWorkingBuffer[512];
    /* 0x20C */ size_t mWorkingBufferLength;
    /* 0x210 */ char mBuffer[512];
    /* 0x410 */ s32 mBufferLength;
    /* 0x414 */ s32 mBufferSeekPosition;
    /* 0x418 */ s32 mLastReadCharacter; // specifically an s32, not a char
    /* 0x41C */ char mCurrentLineContents[512];
    /* 0x61C */ size_t mCurrentColumn; // refers to the file
    /* 0x620 */ size_t mCurrentLineNumber; // refers to the file
    /* 0x624 */ String mFilename;
    /* 0x630 */ bool m_630;
    /* 0x634 */ s32 mCurrentTokenType;
};

}

#endif
