#include "gflBpeDecoderFile.h"

using namespace gfl;

BpeDecoderFile::BpeDecoderFile(File* file, AsyncFileStream* output) {
   mInput = nullptr;
   mFile = file;
   mOutput = output;
   mDecodedData = nullptr;
   mEncodedSize = 0;
   mDecodedSize = 0; 
}