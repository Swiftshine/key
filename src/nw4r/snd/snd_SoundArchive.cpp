#include <nw4r/snd.h>
#include <nw4r/ut.h>

#include <cstring>

namespace nw4r {
namespace snd {

SoundArchive::SoundArchive() : mFileReader(NULL) {
    mExtFileRoot[0] = '/';
    mExtFileRoot[1] = '\0';
}

SoundArchive::~SoundArchive() {}

bool SoundArchive::IsAvailable() const {
    return mFileReader;
}

void SoundArchive::Setup(detail::SoundArchiveFileReader* pReader) {
    mFileReader = pReader;
}

void SoundArchive::Shutdown() {
    mFileReader = NULL;
    mExtFileRoot[0] = '/';
    mExtFileRoot[1] = '\0';
}

u32 SoundArchive::GetPlayerCount() const {
    return mFileReader->GetPlayerCount();
}

u32 SoundArchive::GetGroupCount() const {
    return mFileReader->GetGroupCount();
}

const char* SoundArchive::GetSoundLabelString(u32 id) const {
    return mFileReader->GetSoundLabelString(id);
}

u32 SoundArchive::ConvertLabelStringToSoundId(const char* pLabel) const {
    return mFileReader->ConvertLabelStringToSoundId(pLabel);
}

u32 SoundArchive::ConvertLabelStringToPlayerId(const char* pLabel) const {
    return mFileReader->ConvertLabelStringToPlayerId(pLabel);
}

u32 SoundArchive::ConvertLabelStringToGroupId(const char* pLabel) const {
    return mFileReader->ConvertLabelStringToGroupId(pLabel);
}

u32 SoundArchive::GetSoundUserParam(u32 id) const {
    return mFileReader->GetSoundUserParam(id);
}

SoundType SoundArchive::GetSoundType(u32 id) const {
    return mFileReader->GetSoundType(id);
}

bool SoundArchive::ReadSoundInfo(u32 id, SoundInfo* pInfo) const {
    return mFileReader->ReadSoundInfo(id, pInfo);
}

bool SoundArchive::detail_ReadSeqSoundInfo(u32 id, SeqSoundInfo* pInfo) const {
    return mFileReader->ReadSeqSoundInfo(id, pInfo);
}

bool SoundArchive::detail_ReadStrmSoundInfo(u32 id,
                                            StrmSoundInfo* pInfo) const {
    return mFileReader->ReadStrmSoundInfo(id, pInfo);
}

bool SoundArchive::detail_ReadWaveSoundInfo(u32 id,
                                            WaveSoundInfo* pInfo) const {
    return mFileReader->ReadWaveSoundInfo(id, pInfo);
}

bool SoundArchive::ReadPlayerInfo(u32 id, PlayerInfo* pInfo) const {
    return mFileReader->ReadPlayerInfo(id, pInfo);
}

bool SoundArchive::ReadSoundArchivePlayerInfo(
    SoundArchivePlayerInfo* pInfo) const {
    return mFileReader->ReadSoundArchivePlayerInfo(pInfo);
}

bool SoundArchive::detail_ReadSound3DParam(u32 id, Sound3DParam* pParam) const {
    return mFileReader->ReadSound3DParam(id, pParam);
}

bool SoundArchive::detail_ReadBankInfo(u32 id, BankInfo* pInfo) const {
    return mFileReader->ReadBankInfo(id, pInfo);
}

bool SoundArchive::detail_ReadGroupInfo(u32 id, GroupInfo* pInfo) const {
    return mFileReader->ReadGroupInfo(id, pInfo);
}

bool SoundArchive::detail_ReadGroupItemInfo(u32 groupId, u32 itemId,
                                            GroupItemInfo* pInfo) const {
    return mFileReader->ReadGroupItemInfo(groupId, itemId, pInfo);
}

u32 SoundArchive::detail_GetFileCount() const {
    return mFileReader->GetFileCount();
}

bool SoundArchive::detail_ReadFileInfo(u32 id, FileInfo* pInfo) const {
    return mFileReader->ReadFileInfo(id, pInfo);
}

bool SoundArchive::detail_ReadFilePos(u32 fileId, u32 posId,
                                      FilePos* pPos) const {
    return mFileReader->ReadFilePos(fileId, posId, pPos);
}

ut::FileStream *SoundArchive::detail_OpenFileStream(u32 fileId, void *buffer,
                                                    int size) const
{
	FileInfo fileInfo;
	if (!detail_ReadFileInfo(fileId, &fileInfo))
		return nullptr;

	if (fileInfo.extFilePath)
	{
		ut::FileStream *stream = OpenExtStreamImpl(
			buffer, size, fileInfo.extFilePath, 0, fileInfo.fileSize);

		return stream;
	}

	FilePos filePos;
	if (!detail_ReadFilePos(fileId, 0, &filePos))
		return nullptr;

	GroupInfo groupInfo;
	if (!detail_ReadGroupInfo(filePos.groupId, &groupInfo))
		return nullptr;

	GroupItemInfo itemInfo;
	if (!detail_ReadGroupItemInfo(filePos.groupId, filePos.index, &itemInfo))
		return nullptr;

	u32 itemOffset = groupInfo.offset + itemInfo.offset;
	u32 itemSize = itemInfo.size;

	if (groupInfo.extFilePath)
	{
		ut::FileStream *stream = OpenExtStreamImpl(
			buffer, size, groupInfo.extFilePath, itemOffset, itemSize);

		return stream;
	}
	else
	{
		ut::FileStream *stream = OpenStream(buffer, size, itemOffset, itemSize);

		return stream;
	}
}

ut::FileStream* SoundArchive::detail_OpenGroupStream(u32 id, void* pBuffer,
                                                     int bufferSize) const {
    GroupInfo groupInfo;
    if (!detail_ReadGroupInfo(id, &groupInfo)) {
        return NULL;
    }

    if (groupInfo.extFilePath != NULL) {
        return OpenExtStreamImpl(pBuffer, bufferSize, groupInfo.extFilePath,
                                 groupInfo.offset, groupInfo.size);
    }

    return OpenStream(pBuffer, bufferSize, groupInfo.offset, groupInfo.size);
}

ut::FileStream*
SoundArchive::detail_OpenGroupWaveDataStream(u32 id, void* pBuffer,
                                             int bufferSize) const {
    GroupInfo groupInfo;
    if (!detail_ReadGroupInfo(id, &groupInfo)) {
        return NULL;
    }

    if (groupInfo.extFilePath != NULL) {
        return OpenExtStreamImpl(pBuffer, bufferSize, groupInfo.extFilePath,
                                 groupInfo.waveDataOffset,
                                 groupInfo.waveDataSize);
    }

    return OpenStream(pBuffer, bufferSize, groupInfo.waveDataOffset,
                      groupInfo.waveDataSize);
}

ut::FileStream* SoundArchive::OpenExtStreamImpl(void* pBuffer, int bufferSize,
                                                const char* pExtPath,
                                                u32 offset, u32 size) const {
    char pathBuffer[FILE_PATH_MAX + 1];
    const char* pFullPath;

    if (pExtPath[0] == '/') {
        pFullPath = pExtPath;
    } else {
        u32 fileLen = std::strlen(pExtPath);
        u32 dirLen = std::strlen(mExtFileRoot);

        if (fileLen + dirLen >= FILE_PATH_MAX + 1) {
            return NULL;
        }

        std::strncpy(pathBuffer, mExtFileRoot, dirLen + 1);
        std::strncat(pathBuffer, pExtPath, fileLen + 1);

        pFullPath = pathBuffer;
    }

    return OpenExtStream(pBuffer, bufferSize, pFullPath, offset, size);
}

void SoundArchive::SetExternalFileRoot(const char* pExtFileRoot) {
    u32 len = std::strlen(pExtFileRoot);
    u32 nullPos = len;

    if (pExtFileRoot[len - 1] != '/') {
        mExtFileRoot[len] = '/';
        nullPos++;
    }

    mExtFileRoot[nullPos] = '\0';

    // @bug Long path can overflow mExtFileRoot buffer
    std::strncpy(mExtFileRoot, pExtFileRoot, len);
}

} // namespace snd
} // namespace nw4r
