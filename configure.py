#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "RK5E01",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20240706"
config.dtk_tag = "v1.4.1"
config.objdiff_tag = "v2.5.0"
config.sjiswrap_tag = "v1.1.1"
config.wibo_tag = "0.6.11"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
    f"--defsym VERSION_{config.version}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    "-code_merging all",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []


# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI on",
    "-fp_contract on",
    # "-ipa file",
    # "-pool on",
    #"-multibyte",  # For Wii compilers, replace with `-enc SJIS`
    "-enc SJIS",
    # "-func_align 4",
    "-i src/",
    "-i src/revolution/",
    "-i src/gfl/",
    "-i src/fluff/",
    "-i src/nw4r/g3d/",
    "-i src/nw4r/ut/",
    "-i src/nw4r/lyt/",
    "-i src/nw4r/math/",
    "-i src/nw4r/snd/",
    "-i src/nw4r/ef/",
    "-i src/PowerPC_EABI_Support/",
    "-i src/PowerPC_EABI_Support/MSL/",
    "-i src/PowerPC_EABI_Support/MSL/MSL_C/",
    "-i src/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/",
    "-i src/PowerPC_EABI_Support/MSL/MSL_C++/",
    "-i src/PowerPC_EABI_Support/MetroTRK/",
    "-i src/PowerPC_EABI_Support/Runtime/",
    "-i src/hbm/",
    "-i src/hbm/homebutton/",
    "-i src/hbm/nw4hbm/",
    "-i src/hbm/nw4hbm/lyt/",
    "-i src/hbm/nw4hbm/math/",
    "-i src/hbm/nw4hbm/ut/",
    f"-i build/{config.version}/src/",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]


# Debug flags
if args.debug:
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

cflags_rvl = [
    *cflags_base,
    "-func_align 16",
    "-lang=c99",
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
]

cflags_gfl = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-func_align 4",
    # "-common off",
    # "-inline auto,deferred",
]

cflags_fluff_base = [
    *cflags_base,
    "-RTTI on",
    "-inline auto,deferred",
    "-use_lmw_stmw on",
    "-func_align 4",
]

cflags_fluff_util = [
    *cflags_base,
    "-RTTI on",
    "-inline auto",
    "-use_lmw_stmw on",
    "-func_align 4",
]

cflags_fluff = [
    *cflags_fluff_base,
    "-str reuse,readonly",
]

cflags_fluff_base_no_inline_deferred = [
    *cflags_base,
    "-RTTI on",
    "-use_lmw_stmw on",
    "-func_align 4",
]

cflags_fluff_manager = [
    *cflags_fluff_base_no_inline_deferred,
    "-str reuse",
]

cflags_msl = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-common off",
    "-inline auto,deferred",
]

cflags_MSL_C = [
    *cflags_base,
    "-func_align 4",
]
# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
    "-str reuse,pool,readonly",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
]

config.linker_version = "Wii/1.3"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.3",
        "cflags": cflags_base,
        "host": False,
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "Wii/1.3",
        "cflags": cflags_rel,
        "host": True,
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching

config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "host": False,
        "objects": [
            # Object(NonMatching, "PowerPC_EABI_Support/Runtime/global_destructor_chain.c"),
            # Object(NonMatching, "PowerPC_EABI_Support/Runtime/__init_cpp_exceptions.cpp"),
        ],
    },
    {
        "lib" : "MSL_C",
        "mw_version" : config.linker_version,
        "cflags" : cflags_MSL_C,
        "host": False,
        "objects" : [
            Object(Matching, "PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/rand.c"),
        ],
    },
    {
        "lib" : "revolution",
        "mw_version" : "Wii/1.0",
        "cflags" : [
            *cflags_rvl,
            "-DNDEBUG",
        ],
        "host" : False,
        "progress_category": "sdk",
        "objects" : [
            Object(Matching, "revolution/WPAD/WPAD.c"),
        ],
    },
    {
        "lib" : "nw4r",
        "mw_version" : config.linker_version,
        "cflags" : [
            *cflags_base,
            "-func_align 16",
        ],
        "host" : False,
        "objects" : [
        ],
    },
    {
        "lib" : "homebutton",
        "mw_version" : config.linker_version,
        "cflags" : [
            *cflags_rvl,
            "-DNDEBUG",
            "-sdata 0",
            "-sdata2 0",
            "-enc UTF-8",
        ],
        "host" : False,
        "progress_category": "sdk",
        "objects" : [
            Object(Matching, "hbm/homebutton/HBMAnmController.cpp"),
            Object(Matching, "hbm/homebutton/HBMFrameController.cpp"),
            Object(NonMatching, "hbm/homebutton/HBMGUIManager.cpp"),
        ],
    },
    {
        "lib": "gfl",
        "mw_version": config.linker_version,
        "cflags": [*cflags_gfl, "-pragma \"merge_float_consts on\""],
        "host": False,
        "progress_category": "gfl",
        "objects": [
            Object(Matching,    "gfl/gflAlloc.cpp"),
            Object(NonMatching, "gfl/gflBpeDecoderFile.cpp"),
            Object(Matching,    "gfl/gflChecksum.cpp"),
            Object(NonMatching, "gfl/gflCustomRenderObj.cpp"),
            Object(NonMatching, "gfl/gflFixedMemoryStream.cpp"),
            Object(Matching,    "gfl/gflFixedString.cpp"),
            Object(NonMatching, "gfl/gflGfCompression.cpp"),
            Object(Matching,    "gfl/gflHeap.cpp"),
            Object(NonMatching, "gfl/gflMemory.cpp"),
            Object(Matching,    "gfl/gflMemoryBase.cpp"),
            Object(Matching,    "gfl/gflMemoryManagement.cpp"),
            Object(NonMatching, "gfl/gflParam.cpp"),
            Object(NonMatching, "gfl/gflRenderObj.cpp"),
            Object(NonMatching, "gfl/gflResArchivedFileInfo.cpp"),
            Object(Matching,    "gfl/gflResInfo.cpp"),
            Object(NonMatching, "gfl/gflSoundHandleInner.cpp"),
            Object(NonMatching, "gfl/gflSoundArchiveMng.cpp"),
            Object(NonMatching, "gfl/gflTask.cpp"),
            Object(Matching,    "gfl/gflTaskInfo.cpp"),
            Object(NonMatching, "gfl/gflTimer.cpp"),
            Object(NonMatching, "gfl/gflVec3.cpp"),
        ],
    },
    {
        "lib": "fluff/main",
        "mw_version": config.linker_version,
        "cflags": cflags_fluff,
        "host": False,
        "progress_category": "fluff",
        "objects": [
            Object(Matching, "fluff/main.cpp"),
        ],
    },
    {
        "lib" : "fluff/object/",
        "mw_version": config.linker_version,
        "cflags": cflags_fluff,
        "host": False,
        "progress_category": "fluff",
        "objects": [

            # fluff/object/

            Object(Matching,    "fluff/object/FlfHandleObj.cpp"),
            Object(NonMatching, "fluff/object/FlfGameObj.cpp"),
            Object(NonMatching, "fluff/object/Gimmick.cpp"),
            Object(Matching,    "fluff/object/FlfGameObjLocator.cpp"),
            Object(NonMatching, "fluff/object/SpringBase.cpp"),
        ],
    },
    {
        "lib" : "fluff/manager",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_manager],
        "host": False,
        "progress_category": "fluff",
        "objects": [
            Object(NonMatching, "fluff/manager/GmkBeadManager.cpp"),
            Object(NonMatching, "fluff/manager/GmkMng.cpp"),
            Object(Matching,    "fluff/manager/LevelManager.cpp"),
            Object(Equivalent,  "fluff/manager/StageResourceManager.cpp"),
        ],
    },
    {
        "lib": "fluff/graphics/",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_base_no_inline_deferred],
        "host": False,
        "progress_category": "fluff",
        "objects": [
            Object(NonMatching, "fluff/graphics/Cam.cpp"),
        ]
    },
    {
        "lib": "fluff/graphics/",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_base_no_inline_deferred, "-pragma \"merge_float_consts on\""],
        "host": False,
        "progress_category": "fluff",
        "objects": [
            Object(NonMatching, "fluff/graphics/BgBackImage.cpp"),
            Object(Matching,    "fluff/graphics/BGSTFile.cpp"),
            Object(NonMatching, "fluff/graphics/BGSTList.cpp"),
            Object(NonMatching, "fluff/graphics/FB2Tex.cpp"),
            Object(NonMatching, "fluff/graphics/FullSortScene.cpp"),
            Object(NonMatching, "fluff/graphics/GmkPartsMdlSet.cpp"),
            Object(NonMatching, "fluff/graphics/NwAnmCtrl.cpp"),
        ],
    },
    {
        "lib": "fluff/env/",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_base_no_inline_deferred],
        "host": False,
        "progress_category": "fluff",
        "objects": [
            Object(NonMatching, "fluff/env/EnvObject.cpp"),
            Object(NonMatching, "fluff/env/EnvUnitBase.cpp"),
        ],
    },
    {
        "lib" : "fluff/object/gimmick/",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_base_no_inline_deferred],
        "host": False,
        "progress_category": "fluff",
        "objects": [
            Object(NonMatching, "fluff/object/gimmick/GmkArrowSign.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkAllGetSwitch.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkBeadDrop.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkBeadPopItem.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkCameraControl.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkCamRectCtrl.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkCandleStick.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkCartBtn.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkColAnimMdl.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkMsCarrierGoal.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkSimpleMdl.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkSunriseCurtain.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkTurtle.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkUnderseaSound.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkVictoryStand.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkWarpExit.cpp"),
            Object(NonMatching, "fluff/object/gimmick/GmkWoolRope.cpp"),
        ],
    },

    {
        "lib" : "fluff/object/collision/",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_util, "-pragma \"merge_float_consts on\""],
        "host": False,
        "progress_category": "fluff",
        "objects" : [
            Object(NonMatching, "fluff/object/collision/FlfRideHitBase.cpp"),
            Object(NonMatching, "fluff/object/collision/KdTreeNode.cpp"),
            Object(NonMatching, "fluff/object/collision/KdTree.cpp"),
            Object(NonMatching, "fluff/object/collision/ColObj.cpp"),
        ],
    },
    {
        "lib" : "fluff/util",
        "mw_version": config.linker_version,
        "cflags": [
            *cflags_fluff_util, 
            "-pragma \"merge_float_consts on\"",
        ],
        "host": False,
        "progress_category": "fluff",
        "objects" : [
            Object(Matching, "fluff/object/FlfHandleList.cpp"),
            # fluff/util/
            Object(Matching,    "fluff/util/CollisionFlagUtil.cpp"),
            Object(NonMatching, "fluff/util/FullSortSceneUtil.cpp"),
            Object(NonMatching, "fluff/util/GimmickResource.cpp"),
            Object(NonMatching, "fluff/util/GimmickUtil.cpp"),
            Object(Matching,    "fluff/util/KdTreeUtil.cpp"),
            Object(NonMatching, "fluff/util/MissionUtil.cpp"),
            Object(NonMatching, "fluff/util/SignatureUtil.cpp"),
            Object(Matching,    "fluff/util/SimpleMdlCommon.cpp"),
        ],
    },
    {
        "lib": "fluff/demo",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_util],
        "host": False,
        "progress_category": "fluff",
        "objects": [
            Object(NonMatching, "fluff/demo/DemoObject.cpp"),
            Object(NonMatching, "fluff/demo/FlfDemoCtrl.cpp"),
        ],
    },

        {
        "lib": "fluff/language",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_util],
        "host": False,
        "progress_category": "fluff",
        "objects": [
            Object(NonMatching, "fluff/language/Language.cpp"),
            Object(NonMatching, "fluff/util/NURBSOption.cpp"),
        ],
    },

    {
        "lib" : "fluff/stage",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_util,],
        "host": False,
        "progress_category": "fluff",
        "objects" : [
            # fluff/stage
            Object(NonMatching, "fluff/stage/StageResources.cpp"),

        ],
    },
    {
        "lib" : "fluff/stage/mission",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_util,],
        "host": False,
        "progress_category": "fluff",
        "objects" : [
            # fluff/stage/mission/
            Object(NonMatching, "fluff/stage/mission/MissionClearChecker.cpp"),

        ],
    },
    {
        "lib" : "fluff/stage/work",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_util,],
        "host": False,
        "progress_category": "fluff",
        "objects" : [
            # fluff/work/
            Object(NonMatching, "fluff/work/InStageWork.cpp"),
        ],
    },
]

config.progress_categories = [
    ProgressCategory("fluff", "Game Code"),
    ProgressCategory("gfl", "Good-Feel Library Code"),
    ProgressCategory("sdk", "SDK Code"),
]

config.progress_each_module = args.verbose

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    config.progress_each_module = args.verbose
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
