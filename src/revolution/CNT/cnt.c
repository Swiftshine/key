#include <revolution/CNT.h>
#include <revolution/ESP.h>
#include <revolution/OS.h>

#ifdef __DECOMP_NON_MATCHING
static s32 __CNTConvertErrorCode(s32 error) {
    int i;

    // TODO: Placed in the wrong ELF section
    const s32 errorMap[] = {
        0x0000,  0x0000,  -0x03E9, -0x13C7, -0x03EA, -0x13C7, -0x03EB, -0x13C7,
        -0x03EC, -0x138A, -0x03ED, -0x13C7, -0x03EE, -0x13C7, -0x03EF, -0x13C7,
        -0x03F0, -0x138A, -0x03F1, -0x138B, -0x03F2, -0x13C7, -0x03F3, -0x13C7,
        -0x03F4, -0x13C7, -0x03F5, -0x13C7, -0x03F6, -0x13C7, -0x03F7, -0x13C7,
        -0x03F8, -0x1388, -0x03F9, -0x1391, -0x03FA, -0x13C7, -0x03FB, -0x13C7,
        -0x03FC, -0x13C7, -0x03FD, -0x13C7, -0x03FE, -0x13C7, -0x03FF, -0x13C7,
        -0x0400, -0x1390, -0x0401, -0x13C7, -0x0402, -0x1392, -0x0403, -0x13C7,
        -0x0404, -0x13C7, -0x0405, -0x13C7, -0x0406, -0x13C7, -0x0407, -0x13C7,
        -0x0408, -0x13C7, -0x0409, -0x13C7, -0x040A, -0x13C7, -0x040B, -0x13C7,
        -0x040C, -0x13C7, -0x040D, -0x13C7, -0x040E, -0x13C7, 0x0000,  0x0000,
        -0x0066, -0x1392, -0x0067, -0x1393, -0x0072, -0x1394, -0x0069, -0x13C7,
        -0x0074, -0x1395, -0x0065, -0x1391, -0x006C, -0x13C7, -0x006D, -0x1388,
        -0x006B, -0x13C7, -0x006A, -0x1391, -0x0073, -0x13C7, -0x0068, -0x13C7,
        -0x006F, -0x13C7, -0x0075, -0x13C7, -0x0076, -0x13C7, -0x0077, -0x1407,
        -0x0001, -0x1392, -0x0002, -0x13C7, -0x0003, -0x13C7, -0x0004, -0x1391,
        -0x0005, -0x13C7, -0x0006, -0x1391, -0x0007, -0x13C7, -0x0008, -0x13C7,
        -0x0009, -0x13C7, -0x000A, -0x13C7, -0x000B, -0x13C7, -0x000C, -0x1394,
        -0x000D, -0x13C7, -0x000E, -0x13C7, -0x000F, -0x13C7, -0x0010, -0x13C7,
        -0x0011, -0x13C7, -0x0012, -0x13C7, -0x0013, -0x13C7, -0x0014, -0x13C7,
        -0x0015, -0x13C7, -0x0016, -0x1389, -0x0017, -0x13C7,
    };

    i = 0;

    if (error >= 0) {
        return error;
    }

    for (; i < LENGTHOF(errorMap); i += 2) {
        if (error == errorMap[i]) {
            return errorMap[i + 1];
        }
    }

    OSReport("CAUTION!  Unexpected error code [%d] was found.\n", error);
    return -0x13C7;
}
#else
#error This file has not yet been decompiled accurately. Use "cnt.s" instead.
#endif

s32 contentFastOpenNAND(CNTHandle* handle, s32 entrynum, CNTFileInfo* info) {
    ARCFileInfo arcInfo;

    if (!ARCFastOpen(&handle->arcHandle, entrynum, &arcInfo)) {
        return -0x138A;
    }

    info->handle = handle;
    info->offset = arcInfo.offset;
    info->length = arcInfo.size;
    info->position = 0;

    return 0;
}

s32 contentConvertPathToEntrynumNAND(CNTHandle* handle, const char* path) {
    return ARCConvertPathToEntrynum(&handle->arcHandle, path);
}

u32 contentGetLengthNAND(const CNTFileInfo* info) {
    return info->length;
}

s32 contentReadNAND(CNTFileInfo* info, void* dst, u32 len, s32 offset) {
    if (info->position + offset > info->length) {
        return -0x1391;
    }

    if (ESP_SeekContentFile(info->handle->fd,
                            info->offset + info->position + offset,
                            IPC_SEEK_BEG) < 0) {
        return -0x138C;
    }

    return __CNTConvertErrorCode(
        ESP_ReadContentFile(info->handle->fd, dst, len));
}

s32 contentCloseNAND(CNTFileInfo* info) {
#pragma unused(info)

    return 0;
}
