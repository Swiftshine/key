#include "mapdata/Mapdata.h"
#include "gfl/gflResFileInfo.h"
#include "util/GimmickUtil.h"
#include "object/collision/ColDataWrapper.h"

extern "C" u64 GetCollisionTypeAndAttribute(const std::string& rDescription, bool isInMission);

#define GET_AT_OFFSET(T, mapbin, offset) (reinterpret_cast<T*>(BYTE_PTR(mapbin) + offset))

Mapdata* Mapdata::Parse(const char* pFilepath, bool isInMission) {
    gfl::ResFileObject rfo;
    gfl::ResFileObject::FromArchive(rfo, pFilepath);

    Mapbin* mapbin = rfo.GetData<Mapbin>();

    Mapdata* mapdata = new Mapdata;

    mapdata->mBoundsMin = mapbin->mBoundsMin;
    mapdata->mBoundsMax = mapbin->mBoundsMax;

    float version = mapbin->mVersion;

    std::vector<int> gimmickIDs;
    std::vector<u64> collisionTypes;
    std::vector<std::string> wallLabels;
    size_t zoneOffset = 0;
    size_t numZones = 0;
    size_t courseInfoOffset = 0;
    size_t numCourseInfo = 0;
    size_t wallOffset = mapbin->mWallOffset;
    size_t labeledWallOffset = mapbin->mLabeledWallOffset;
    size_t commonGimmickOffset = mapbin->mCommonGimmickOffset;
    size_t gimmickOffset = mapbin->mGimmickOffset;
    size_t pathOffset = mapbin->mPathOffset;
    size_t numWalls = mapbin->mNumWalls;
    size_t numLabeledWalls = mapbin->mNumLabeledWalls;
    size_t numCommonGimmicks = mapbin->mNumCommonGimmicks;
    size_t numGimmicks = mapbin->mNumGimmicks;
    size_t numPaths = mapbin->mNumPaths;

    size_t* pair = &mapbin->mNumPaths + 1;

    if (version >= 3.1f) {
        numZones = pair[0];
        zoneOffset = pair[1];

        pair += 2;
    }

    if (version >= 3.3f) {
        numCourseInfo = pair[0];
        courseInfoOffset = pair[1];

        pair += 2;
    }

    size_t commonGimmickNameOffset = pair[0];
    size_t wallTypeOffset = pair[1];
    size_t wallLabelOffset = pair[2];

    mapdata->mNumWalls = numWalls;
    mapdata->mWalls = nullptr;
    mapdata->mNumLabeledWalls = numLabeledWalls;
    mapdata->mLabeledWalls = nullptr;
    mapdata->mNumCommonGimmicks = numCommonGimmicks;
    mapdata->mCommonGimmickBuildInfos = nullptr;
    mapdata->mCommonGimmicks = nullptr;
    mapdata->mNumGimmicks = numGimmicks;
    mapdata->mGimmicks = nullptr;
    mapdata->mNumPaths = numPaths;
    mapdata->mPaths = nullptr;
    mapdata->mNumZones = numZones;
    mapdata->mZones = nullptr;
    mapdata->mNumCourseInfo = numCourseInfo;
    mapdata->mCourseInfos = nullptr;

    // common gimmick names
    StringTable* table = GET_AT_OFFSET(StringTable, mapbin, commonGimmickNameOffset);
    for (uint i = 0; i < table->mCount; i++) {
        string32 buf;

        for (uint j = 0; j < sizeof(string32); j++) {
            buf[j] = table->mStrings[i][j];
        }

        std::string name = buf;
        int id = GimmickUtil::GetGimmickIDByCommonGimmickName(name.c_str());
        gimmickIDs.push_back(id);
    }

    // wall collision types
    table = GET_AT_OFFSET(StringTable, mapbin, wallTypeOffset);
    for (uint i = 0; i < table->mCount; i++) {
        string32 buf;

        for (uint j = 0; j < sizeof(string32); j++) {
            buf[j] = table->mStrings[i][j];
        }

        std::string type = buf;
        u64 colType = GetCollisionTypeAndAttribute(type, isInMission);
        collisionTypes.push_back(colType);
    }

    // wall labels
    table = GET_AT_OFFSET(StringTable, mapbin, wallLabelOffset);
    for (uint i = 0; i < table->mCount; i++) {
        string32 buf;

        for (uint j = 0; j < sizeof(string32); j++) {
            buf[j] = table->mStrings[i][j];
        }

        std::string label = buf;
        wallLabels.push_back(label);
    }

    if (numWalls != 0) {
        ColDataSeg* walls = new ColDataSeg[numWalls];
        MapdataWall* wallArray = GET_AT_OFFSET(MapdataWall, mapbin, wallOffset);

        for (uint i = 0; i < numWalls; i++) {
            size_t* indices = ColDataSeg::CopyFromBinary(&walls[i], wallArray);
            wallArray = (MapdataWall*)(indices + 1);
            walls[i].mFlags = collisionTypes[indices[0]];
        }

        mapdata->mWalls = walls;
    }

    if (numLabeledWalls != 0) {
        ColDataSegLabel* labeledWalls = new ColDataSegLabel[numLabeledWalls];
        MapdataLabeledWall* labeledWallArray = GET_AT_OFFSET(MapdataLabeledWall, mapbin, labeledWallOffset);

        for (uint i = 0; i < numLabeledWalls; i++) {
            size_t* indices = ColDataSeg::CopyFromBinary(&labeledWalls[i], labeledWallArray);
            labeledWallArray = (MapdataLabeledWall*)(indices + 2);
            labeledWalls[i].mFlags = collisionTypes[indices[0]];
            labeledWalls[i].mLabel = wallLabels[indices[1]];
        }

        mapdata->mLabeledWalls = labeledWalls;
    }


    if (numCommonGimmicks != 0) {
        // CommonGimmickBuildInfo* buildInfos = new CommonGimmickBuildInfo[numCommonGimmicks];
        // MapdataCommonGimmick* commonGimmicks = new MapdataCommonGimmick[numCommonGimmicks];


    }
    // not finished
    return mapdata;
}
