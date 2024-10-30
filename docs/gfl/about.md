# **G**ood-**F**eel **L**ibrary
Good-Feel's proprietary programming library. As Good-Feel was a relatively new company at the time, GFL changed a lot.

*Kirby's Epic Yarn* uses a version of GFL we can call v2, with v1 being used in the prior Good-Feel game, *Wario Land - Shake It!*.

Here's a (by no means complete) list of what GFLv2 has:

| GFLv2 | Usage | v1 Equivalent | v2 Relatives |
| - | - | - | - |
| `AsyncFileStream` | - | `ASyncFileStream`, `ASyncDecodeReqQue` | None. |
| `BpeDecoderFile` | Used to decode data from [GF Archives](https://swiftshine.github.io/doc/gfa.html) that were encoded with [Byte Pair Encoding](https://en.wikipedia.org/wiki/Byte_pair_encoding). | `BpeDecoderFile` | None. |
| `File` | File management. | `File`, `FileRevo`, `FileSystem` | `File`, `FileSystem`, `FileWii`, `FileSystemWii` |
| `Functor` | Function pointers, for things such as states or callbacks. | No such module present. | `FunctorBase`, `FunctorClassMethod`, `FunctorFunc`, `FunctorImpl` |
| `Memory` | Memory management. |`Memory` or `MemoryRevo` | `MemoryBase`, `Memory` |
| `Param` | Parameter processing and management. | No such module present.| `ParamBool`, `ParamStr`, `ParamF32`, `ParamS32`, `ParamGroup`, `ParamBoolA`, `ParamStrA`, `ParamF32A`, `ParamS32A` |
| `ResInfo` | Used to read from files (`ResFileInfo`), or files within GF Archives (`ResArchivedFileInfo`). | No such module present. | `ResInfo`, `ResFileInfo`, `ResArchivedFileInfo` |
| `ScnMdlWrapper` | Simplifies nw4r model rendering and management. | `ScnMdlWrapper`| None(?).|
| `Sound` | Sound management. | `Sound` or `SoundRevo` (and related)| `Sound`, `SoundQue`, `SoundHandleInner`, `SoundArchiveMng`, `(I)SoundFadeCtrl`, `SD3DActor`(?) | 
| `Task` | Used to manage various tasks. |  `Proc` (for "process") (and related) | `Task`, `BgArchiveLoadTask`, `BgTask`, `DrawRootTask`, `GameRootTask`, `RootTask` |

