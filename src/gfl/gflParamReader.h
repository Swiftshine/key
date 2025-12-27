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

        unsigned int m_0;
        unsigned int m_4;
        const char* mString;

    };

    /* Structures */

    ENUM_CLASS(TokenType,
        End             = -1,
        Invalid         = 0,
        LeftBrace       = 1, // {
        RightBrace      = 2, // }
        LeftParen       = 3, // (
        RightParen      = 4, // )
        LeftBracket     = 5, // [
        RightBracket    = 6, // ]
        Comma           = 7, // ,
        Assignment      = 8, // =
        Minus           = 9, // -
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


    
    ParamReader(FixedMemoryStream* pMemoryStream);
    ~ParamReader();

    /* Class Methods */
    /// @return a `TokenType`.
    int ParseToken();
    const char* GetTokenString(int tokenType);
    void fn_80652EC8();
    void Reset(int unused = 1) DONT_INLINE_CLASS;
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
    
    inline int ReadCharacter() {
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
    

    bool IsAlphabetic(int character) {
        if (character - 'A' < 26 || character - 'a' < 26) {
            return true;
        }

        return false;
    }

    bool IsNumeric(int character) {
        if (character - '0' <= 9 || character == '.') {
            return true;
        }

        return false;
    }

    bool IsNewline(int character) {
        if (character == '\r' || character == '\n') {
            return true;
        }

        return false;
    }
    
    bool IsWhitespace(int character) {
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
    /* 0x004 */ int mIntValue;
    /* 0x008 */ float mFloatValue;
    /* 0x00C */ char mWorkingBuffer[512];
    /* 0x20C */ size_t mWorkingBufferLength;
    /* 0x210 */ char mBuffer[512];
    /* 0x410 */ int mBufferLength;
    /* 0x414 */ int mBufferSeekPosition;
    /* 0x418 */ int mLastReadCharacter; // specifically an int, not a char
    /* 0x41C */ char mCurrentLineContents[512];
    /* 0x61C */ size_t mCurrentColumn; // refers to the file
    /* 0x620 */ size_t mCurrentLineNumber; // refers to the file
    /* 0x624 */ String mFilename;
    /* 0x630 */ bool m_630;
    /* 0x634 */ int mCurrentTokenType;
};

}

#endif