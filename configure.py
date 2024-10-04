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
    "--no-asm",
    action="store_true",
    help="don't incorporate .s files from asm directory",
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
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.debug = args.debug
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
if not is_windows():
    config.wrapper = args.wrapper
if args.no_asm:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20231018"
config.dtk_tag = "v0.9.4"
config.sjiswrap_tag = "v1.1.1"
config.wibo_tag = "0.6.11"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-i include",
    f"-I build/{config.version}/include",
    f"--defsym version={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    # "-warn off",
    "-listclosure", # Uncomment for Wii linkers
]
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
    "-func_align 4",
    "-i src/",
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
    "-i src/revolution",
    f"-i build/{config.version}/src/",
    f"-DVERSION={version_num}",
]


# Debug flags
if config.debug:
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

cflags_gfl = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    # "-common off",
    # "-inline auto,deferred",
]

cflags_fluff_base = [
    *cflags_base,
    "-RTTI on",
    "-inline auto,deferred",
    "-use_lmw_stmw on",
]

cflags_fluff_util = [
    *cflags_base,
    "-RTTI on",
    "-inline auto",
    "-use_lmw_stmw on",
]

cflags_fluff = [
    *cflags_fluff_base,
    "-str reuse,readonly",
]

cflags_fluff_base_no_inline_deferred = [
    *cflags_base,
    "-RTTI on",
    "-use_lmw_stmw on",
]

cflags_fluff_manager = [
    *cflags_fluff_base_no_inline_deferred,
    "-str reuse"
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
        "mw_version" : config.linker_version,
        "clags" : cflags_base,
        "host" : False,
        "objects" : [

        ],
    },
    {
        "lib" : "nw4r",
        "mw_version" : config.linker_version,
        "clags" : [
            *cflags_base,
            # "-func_align 4",
        ],
        "host" : False,
        "objects" : [
        ],
    },
    {
        "lib" : "homebutton",
        "mw_version" : config.linker_version,
        "cflags" : [
            *cflags_base,
        ],
        "host" : False,
        "objects" : [
            # Object(NonMatching, "homebutton/GroupAnmController.cpp"),
        ],
    },
    {
        "lib": "gfl",
        "mw_version": config.linker_version,
        "cflags": [*cflags_gfl, "-pragma \"merge_float_consts on\""],
        "host": False,
        "objects": [
            Object(Matching, "gfl/gflGfCompression.cpp"),
            Object(NonMatching, "gfl/gflMemory.cpp"),
            Object(NonMatching, "gfl/gflHeap.cpp"),
            Object(Matching, "gfl/gflMemoryManagement.cpp"),
            Object(Matching, "gfl/gflAlloc.cpp"),
            Object(NonMatching, "gfl/gflFixedMemoryStream.cpp"),
            Object(Matching, "gfl/gflVec3.cpp"),
            Object(Matching, "gfl/gflMemoryBase.cpp"),
            Object(NonMatching,    "gfl/gflFixedString.cpp"),
            Object(Matching,    "gfl/gflChecksum.cpp"),
            Object(NonMatching,     "gfl/gflTaskInfo.cpp"),
            Object(NonMatching,     "gfl/gflTask.cpp"),
            Object(Matching,    "gfl/gflResInfo.cpp"),
            Object(NonMatching, "gfl/gflResArchivedFileInfo.cpp"),
            Object(NonMatching, "gfl/gflParam.cpp"),
            Object(NonMatching, "gfl/gflRenderObj.cpp"),
            Object(NonMatching, "gfl/gflCustomRenderObj.cpp"),
        ],
    },
    {
        "lib": "fluff/main",
        "mw_version": config.linker_version,
        "cflags": cflags_fluff,
        "host": False,
        "objects": [
            Object(Matching, "fluff/main.cpp"),
        ],
    },
    {
        "lib" : "fluff",
        "mw_version": config.linker_version,
        "cflags": cflags_fluff,
        "host": False,
        "objects": [

            # fluff/object/

            Object(Matching,    "fluff/object/FlfHandleObj.cpp"),
            Object(NonMatching, "fluff/object/FlfGameObj.cpp"),
            Object(NonMatching, "fluff/object/Gimmick.cpp"),
            Object(NonMatching,    "fluff/object/FlfHandleList.cpp"),
            Object(Matching,    "fluff/object/FlfGameObjLocator.cpp"),

        ],
    },
    {
        "lib" : "fluff/manager",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_manager],
        "host": False,
        "objects": [
            Object(NonMatching, "fluff/manager/StageResourceManager.cpp"),
            Object(Matching, "fluff/manager/LevelManager.cpp"),
        ],
    },
    {
        "lib": "fluff/graphics/",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_base_no_inline_deferred, "-pragma \"merge_float_consts on\""],
        "host": False,
        "objects": [
            Object(NonMatching, "fluff/graphics/NwAnmCtrl.cpp"),
            Object(NonMatching, "fluff/graphics/BgBackImage.cpp"),
            Object(Matching, "fluff/graphics/BGSTFile.cpp"),
        ],
    },
    {
        "lib" : "fluff/object/gmk/",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff,],
        "host": False,
        "objects": [
            Object(NonMatching, "fluff/object/gmk/GmkCamRectCtrl.cpp"),
            Object(NonMatching, "fluff/object/gmk/GmkColAnimMdl.cpp"),
            Object(NonMatching, "fluff/object/gmk/GmkSimpleMdl.cpp"),
            Object(NonMatching, "fluff/object/gmk/GmkWoolRope.cpp"),
        ],
    },

    {
        "lib" : "fluff/object/collision/",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_util, "-pragma \"merge_float_consts on\""],
        "host": False,
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
        "cflags": [*cflags_fluff_util, "-pragma \"merge_float_consts on\""],
        "host": False,
        "objects" : [
            # fluff/util/
            Object(Matching, "fluff/util/CollisionFlagUtil.cpp"),
            Object(Matching, "fluff/util/SimpleMdlCommon.cpp"),
            Object(NonMatching, "fluff/util/MissionUtil.cpp"),
            Object(NonMatching, "fluff/util/SignatureUtil.cpp"),
            Object(NonMatching, "fluff/util/GimmickUtil.cpp"),
            Object(Matching, "fluff/util/KdTreeUtil.cpp"),
            Object(NonMatching, "fluff/util/FullSortSceneUtil.cpp"),
        ],
    },
    {
        "lib" : "fluff/sage",
        "mw_version": config.linker_version,
        "cflags": [*cflags_fluff_util,],
        "host": False,
        "objects" : [
            # fluff/stage
            Object(NonMatching, "fluff/stage/StageResources.cpp"),

        ],
    },
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    config.progress_each_module = args.verbose
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
