#include <cstring>
#include "gflParamReader.h"

using namespace gfl;

extern "C" void GFL_HALT();

const char* TokenTypes[] = {
    "TOKEN_INVALID",

};

ParamReader::~ParamReader() { }

// https://decomp.me/scratch/FtDVG
s32 ParamReader::ParseToken() {
    mWorkingBufferLength = 0;
    mWorkingBuffer[0] = '\0';

    if (mLastReadCharacter == -2) {
        mLastReadCharacter = ReadCharacter();
    }

    fn_80652EC8();

    s32 lastRead = mLastReadCharacter;

    if (lastRead < 0) {
        return ParamReader::eTokenType_End;
    }

    if (lastRead == '[') {
        ReadCharacter();
        return ParamReader::eTokenType_LeftBracket;
    }

    if (lastRead == ',') {
        ReadCharacter();
        return ParamReader::eTokenType_Comma;
    }

    if (lastRead == ')') {
        ReadCharacter();
        return ParamReader::eTokenType_RightParen;
    }

    if (lastRead == '(') {
        ReadCharacter();
        return ParamReader::eTokenType_LeftParen;
    }

    if (lastRead == '=') {
        ReadCharacter();
        return ParamReader::eTokenType_Assignment;
    }

    if (lastRead == '-') {
        ReadCharacter();
        return ParamReader::eTokenType_Minus;
    }

    if (lastRead == '{') {
        ReadCharacter();
        return ParamReader::eTokenType_LeftBrace;
    }

    if (lastRead == ']') {
        ReadCharacter();
        return ParamReader::eTokenType_RightBracket;
    }

    if (lastRead == '}') {
        ReadCharacter();
        return ParamReader::eTokenType_RightBracket;
    }


    if (IsNumeric(lastRead)) {
        // maybe alphabetic
        bool isAlphabetic = IsAlphabetic(lastRead);

        if (isAlphabetic) {
            ReadCharacter();

            while (true) {
                lastRead = mLastReadCharacter;

                isAlphabetic = IsAlphabetic(lastRead);

                if (!isAlphabetic && lastRead - '0' > 9 && lastRead != '_' && lastRead != '.') {
                    UpdateWorkingBuffer('\0');

                    if (strcmp(mWorkingBuffer, "true") == 0 || strcmp(mWorkingBuffer, "TRUE") == 0) {
                        return ParamReader::eTokenType_ValueTrue;
                    }

                    if (strcmp(mWorkingBuffer, "false") == 0 || strcmp(mWorkingBuffer, "FALSE") == 0) {
                        return ParamReader::eTokenType_ValueFalse;
                    }

                    if (strcmp(mWorkingBuffer, "s32") == 0) {
                        return ParamReader::eTokenType_TypeS32;
                    }

                    if (strcmp(mWorkingBuffer, "f32") == 0) {
                        return ParamReader::eTokenType_TypeF32;
                    }

                    if (strcmp(mWorkingBuffer, "str") == 0) {
                        return ParamReader::eTokenType_TypeString;
                    }

                    if (strcmp(mWorkingBuffer, "bool") == 0) {
                        return ParamReader::eTokenType_TypeBool;
                    }

                    return ParamReader::eTokenType_Identifier;
                }

                UpdateWorkingBuffer(lastRead);

                ReadCharacter();
            }
        }

        if (lastRead != '\"') {
            if (lastRead != '#') {
                return ParamReader::eTokenType_Invalid;
            }

            ReadCharacter();

            while (true) {
                s32 lastRead = mLastReadCharacter;
                bool isNewline = IsNewline(lastRead);

                if (isNewline || lastRead < 0) {
                    UpdateWorkingBuffer('\0');
                    return ParamReader::eTokenType_Description;
                }

                UpdateWorkingBuffer(lastRead);
                ReadCharacter();
            }
        }

        ReadCharacter();

        for (s32 lastRead = mLastReadCharacter; lastRead != '\"'; ) {
            bool isNewline = IsNewline(lastRead);

            if (isNewline || lastRead < 0) {
                break;
            }

            UpdateWorkingBuffer(lastRead);
            ReadCharacter();
        }

        if (lastRead == '\"') {
            ReadCharacter();
        }

        UpdateWorkingBuffer('\0');
        return ParamReader::eTokenType_ValueString;
    } else {
        // maybe numeric

        UpdateWorkingBuffer(lastRead);
        ReadCharacter();

        bool isFloat = false;

        while (true) {
            s32 lastRead = mLastReadCharacter;

            if (!IsNumeric(lastRead) && lastRead != 'f') {
                goto END;
            }

            if (lastRead == '.' || lastRead == 'f') {
                isFloat = true;
            }

            if (lastRead == 'f') {
                break;
            }

            UpdateWorkingBuffer(lastRead);
            ReadCharacter();
        }

        ReadCharacter();
END:
        UpdateWorkingBuffer('\0');

        if (isFloat) {
            mFloatValue = static_cast<f32>(strtod(mWorkingBuffer, nullptr));
            return ParamReader::eTokenType_ValueF32;
        }

        mFloatValue = static_cast<f32>(strtol(mWorkingBuffer, nullptr, 10));
        return ParamReader::eTokenType_ValueS32;
    }
}

const char* ParamReader::GetTokenString(s32 tokenType) {
    switch (tokenType) {
        case ParamReader::eTokenType_Invalid:        return "INVALID TOKEN";
        case ParamReader::eTokenType_LeftBrace:      return "{";
        case ParamReader::eTokenType_RightBrace:     return "}";
        case ParamReader::eTokenType_LeftParen:      return "(";
        case ParamReader::eTokenType_RightParen:     return ")";
        case ParamReader::eTokenType_LeftBracket:    return "[";
        case ParamReader::eTokenType_RightBracket:   return "]";
        case ParamReader::eTokenType_Comma:          return ",";
        case ParamReader::eTokenType_Assignment:     return "=";
        case ParamReader::eTokenType_Minus:          return "-";
        case ParamReader::eTokenType_TypeS32:        return "s32";
        case ParamReader::eTokenType_TypeF32:        return "f32";
        case ParamReader::eTokenType_TypeString:     return "str";
        case ParamReader::eTokenType_TypeBool:       return "bool";
        case ParamReader::eTokenType_ValueS32:       return "s32 number";
        case ParamReader::eTokenType_ValueF32:       return "f32 number";
        case ParamReader::eTokenType_ValueTrue:      return "true";
        case ParamReader::eTokenType_ValueFalse:     return "false";
        case ParamReader::eTokenType_Identifier:     return "identifier";
        case ParamReader::eTokenType_ValueString:    return "string";
        case ParamReader::eTokenType_Description:    return "#description";
        case ParamReader::eTokenType_End:            return "END";

        default:                        return "UNKNOWN TOKEN";
    }
}

// https://decomp.me/scratch/0pegK
// (not done)
void ParamReader::fn_80652EC8() {
    s32 lastRead;

    while (true) {
        lastRead = mLastReadCharacter;
        if (!IsWhitespace(lastRead)) {
            while (!IsNewline(lastRead)) {
                if (lastRead < 0 || lastRead != '/') {
                    return;
                }

                lastRead = ReadCharacter();
                mLastReadCharacter = lastRead;

                if (lastRead != '/') {
                    return;
                }
            }
        }

        mLastReadCharacter = ReadCharacter();
        Reset();
    }
}
void ParamReader::Reset(s32) { // argument is unused
    s32 lastRead = ReadCharacter();

    while (!IsNewline(lastRead) && lastRead >= 0) {
        lastRead = ReadCharacter();
    }

    if (IsNewline(lastRead)) {
        s32 col = mCurrentColumn;
        if (col >= 2) {
            mCurrentLineContents[mCurrentColumn - 2] = '\0';
        } else if (col >= 1) {
            mCurrentLineContents[mCurrentColumn - 1] = '\0';
        }
    } else {
        mCurrentLineContents[mCurrentColumn] = '\0';
    }
}

ParamReader::ParamReader(FixedMemoryStream* pMemoryStream)
    : mFixedMemoryStream(pMemoryStream)
    , mIntValue(0)
    , mFloatValue(0.0f)
    , mWorkingBufferLength(0)
    , mBufferLength(0)
    , mBufferSeekPosition(0)
    , mLastReadCharacter(-2)
    , mCurrentColumn(0)
    , mCurrentLineNumber(1)
    , mFilename()
{
    memset(mWorkingBuffer, 0, sizeof(mWorkingBuffer));
    memset(mCurrentLineContents, 0, sizeof(mCurrentLineContents));
    m_630 = false;
}
