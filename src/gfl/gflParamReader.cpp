#pragma ipa file
#include "gflParamReader.h"

using namespace gfl;

// https://decomp.me/scratch/gZhIe
ParamReader::~ParamReader() { }

int ParamReader::GetTokenType() {
    int unk;
    
    mParamGroupNameLength = 0;
    mParamGroupName[0] = '\0';

    if (mLastReadCharacter == -2) {
        if (mBufferSeekPosition == mBufferSize) {
            size_t numRead = mFixedMemoryStream->Read(mBuffer, sizeof(mBuffer));
            mBufferSize = numRead;

            if (numRead != 0) {
                mBufferSeekPosition = 0;
            }
        }
    }
}