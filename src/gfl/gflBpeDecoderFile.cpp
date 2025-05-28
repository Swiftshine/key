#include "gflAsyncFileStream.h"
#include "gflBpeDecoderFile.h"
#include "gflGfArch.h"
#include "gflGfCompression.h"
#include "gflMemoryManagement.h"

using namespace gfl;

BpeDecoderFile::BpeDecoderFile(File* pFile, size_t inputStreamPos) {
   mInputStream = nullptr;
   mFile = pFile;
   mInputStreamPos = inputStreamPos;
   Reset();
}


BpeDecoderFile::~BpeDecoderFile() { }

void* BpeDecoderFile::Decode(u8 heapID, size_t* pDecompressedSize, uint align) {
	PrepareDecode();

   *pDecompressedSize = mDecodedSize;
   size_t streamPos = mInputStreamPos;
   void* output = gfl::Alloc(heapID, mDecodedSize, align);

   mInputStream.Create(new gfl::AsyncFileStream(mFile, mEncodedSize, streamPos + GFARCH_COMPRESSION_HEADER_SIZE));

   // input stream points to the start of the BPE encoded data
   mDecodedData = output;

   u8 left[256], left2[256], right[256], stack[256];

   memset(left,  0, sizeof(left));
   memset(right, 0, sizeof(right));
   memset(stack, 0, sizeof(stack));

   // unpack each block until EOF

   // set left to itself as literal flag
	for (int i = 0; i < 256; i++) {
		left[i] = i;
	}

   int count;
   
LAB_80645298:
	{
      	AsyncFileStream* stream = mInputStream;

		if (stream->m_28 < stream->mCompressedSize) {
			if (stream->m_1C == 0) {
				stream->Update();
			}
		} else {
			AsyncFileStreamManager::Instance()->Reset(stream);
			count = -1;
		}
	}

	if (count < 0) {
		mInputStream.Destroy();
		DCStoreRange(output, mDecodedSize);
		return output;
	}

	memcpy(left, left2, sizeof(left));
	memset(right, 0, sizeof(right));
}
