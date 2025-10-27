#include <cstring>
#include "gflParamReader.h"

using namespace gfl;

ParamReader::~ParamReader() { }

// https://decomp.me/scratch/FtDVG
int ParamReader::ParseToken() {    
    mWorkingBufferLength = 0;
    mWorkingBuffer[0] = '\0';

    if (mLastReadCharacter == 0xFFFFFFFE) {
        ReadCharacter();
    }

    fn_80652EC8();

    int lastRead = mLastReadCharacter;

    if (lastRead < 0) {
        return TokenType::End;
    }

    if (lastRead == '[') {
        ReadCharacter();
        return TokenType::LeftBracket;
    }

    if (lastRead == ',') {
        ReadCharacter();
        return TokenType::Comma;
    }

    if (lastRead == ')') {
        ReadCharacter();
        return TokenType::RightParen;
    }

    if (lastRead == '(') {
        ReadCharacter();
        return TokenType::LeftParen;
    }

    if (lastRead == '=') {
        ReadCharacter();
        return TokenType::Assignment;
    }

    if (lastRead == '-') {
        ReadCharacter();
        return TokenType::Minus;
    }

    if (lastRead == '{') {
        ReadCharacter();
        return TokenType::LeftBrace;
    }

    if (lastRead == ']') {
        ReadCharacter();
        return TokenType::RightBracket;
    }

    if (lastRead == '}') {
        ReadCharacter();
        return TokenType::RightBracket;
    }


    if (lastRead - '0' > 9 && lastRead != '.') {
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
                        return TokenType::ValueTrue;
                    }

                    if (strcmp(mWorkingBuffer, "false") == 0 || strcmp(mWorkingBuffer, "FALSE") == 0) {
                        return TokenType::ValueFalse;
                    }

                    if (strcmp(mWorkingBuffer, "s32") == 0) {
                        return TokenType::TypeS32;
                    }

                    if (strcmp(mWorkingBuffer, "f32") == 0) {
                        return TokenType::TypeF32;
                    }

                    if (strcmp(mWorkingBuffer, "str") == 0) {
                        return TokenType::TypeString;
                    }

                    if (strcmp(mWorkingBuffer, "bool") == 0) {
                        return TokenType::TypeBool;
                    }

                    return TokenType::Identifier;
                }

                UpdateWorkingBuffer(lastRead);

                ReadCharacter();
            }
        }

        if (lastRead != '\"') {
            if (lastRead != '#') {
                return TokenType::Invalid;
            }

            ReadCharacter();

            while (true) {
                int lastRead = mLastReadCharacter;
                bool isNewline = IsNewline(lastRead);

                if (isNewline || lastRead < 0) {
                    UpdateWorkingBuffer('\0');
                    return TokenType::Description;
                }

                UpdateWorkingBuffer(lastRead);
                ReadCharacter();
            }
        }

        ReadCharacter();

        for (int lastRead = mLastReadCharacter; lastRead != '\"'; ) {
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
        return TokenType::ValueString;
    } else {
        // maybe numeric

        UpdateWorkingBuffer(lastRead);
        ReadCharacter();

        bool isFloat = false;

        while (true) {
            int lastRead = mLastReadCharacter;

            if (lastRead - '0' > 9 && lastRead != '.' && lastRead != 'f') {
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
            mCurrentValue = strtod(mWorkingBuffer, nullptr);
            return TokenType::ValueF32;
        }

        mCurrentValue = static_cast<float>(strtol(mWorkingBuffer, nullptr, 10));
        return TokenType::ValueS32;
    }
}

const char* ParamReader::GetTokenString(int tokenType) {
    switch (tokenType) {
        case TokenType::Invalid:        return "INVALID TOKEN";
        case TokenType::LeftBrace:      return "{";
        case TokenType::RightBrace:     return "}";
        case TokenType::LeftParen:      return "(";
        case TokenType::RightParen:     return ")";
        case TokenType::LeftBracket:    return "[";
        case TokenType::RightBracket:   return "]";
        case TokenType::Comma:          return ",";
        case TokenType::Assignment:     return "=";
        case TokenType::Minus:          return "-";
        case TokenType::TypeS32:        return "s32";
        case TokenType::TypeF32:        return "f32";
        case TokenType::TypeString:     return "str";
        case TokenType::TypeBool:       return "bool";
        case TokenType::ValueS32:       return "s32 number";
        case TokenType::ValueF32:       return "f32 number";
        case TokenType::ValueTrue:      return "true";
        case TokenType::ValueFalse:     return "false";
        case TokenType::Identifier:     return "identifier";
        case TokenType::ValueString:    return "string";
        case TokenType::Description:    return "#description";
        case TokenType::End:            return "END";
        
        default:                        return "UNKNOWN TOKEN";
    }
}