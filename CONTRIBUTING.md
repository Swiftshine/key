# Contributing
If you have questions or are interested in contributing, consider asking in the [GC/Wii Decompilation Discord](https://discord.gg/hKx3FJJgrV) in the `#key` channel.

Sections:
- [Resources](#resources)
- [Code style](#code-style)
    - [Function signatures](#function-signatures)
    - [Function contents](#function-contents)
    - [Enums](#enums)
    - [Structures](#structures)
    - [Conditionals](#conditionals)
    - [Literals](#literals)
    - [Files](#files)

## Resources
- [Ghidra](https://ghidra-sre.org/) - A disassembling, decompiling, and reverse-engineering tool.
    - Using these [custom Ghidra builds](https://github.com/encounter/ghidra-ci/releases) is recommended.
    - Access to the shared Ghidra project for *Kirby's Epic Yarn* and other Good-Feel titles can be requested in the `#ghidra` channel in the [GC/Wii Decompilation Discord](https://discord.gg/hKx3FJJgrV).
- [Objdiff](https://github.com/encounter/objdiff) - A local diffing tool.

## Code style
### Function signatures
No known Good-Feel title was shipped with debug symbols. However, many Good-Feel titles are compiled with [RTTI](https://en.wikipedia.org/wiki/Run-time_type_information). Therefore, all symbol names must be inferred from RTTI or from what the function does.

Function names written by Good-Feel in *Kirby's Epic Yarn* are known to be named with PascalCase -- to mimic Good-Feel's own programming, functions in this decompilation will, too.

Inline functions should use the `inline` keyword to indicate such.

Unknown virtual functions are to be named based on their offset relative to the start of the [virtual table](https://en.wikipedia.org/wiki/Virtual_method_table), prefixed with "vf".

```cpp
class MyClass {
public:
    virtual void KnownFunction();
    // located 0xC bytes after the start of the vtable
    virtual void vfC(); 
    virtual void vf10();
    virtual void AnotherKnownFunction();
    virtual void vf18();
};
```

### Function contents
Functions that don't require code to be written, i.e. a `void` function that does nothing, should have the `return` keyword for the sake of clarity.

```cpp
void DoesNothing() {
    return;
}
```

If a function is not 100% matching, leave a comment above the function with a link to the associated [decomp.me](https://decomp.me) scratch. Remove it once the function has been matched.

```cpp
// https://decomp.me/scratch/EXAMPLE
void MyClass::SomeFunction() {
    ...
}
```

### Enums
C++03 does not allow you to refer to an enum by the name of its enumeration. To get around this, use the `ENUM_CLASS` macro.
```cpp
ENUM_CLASS(EnumName,

    EnumValue0,
    EnumValue1,
    ...
);

int x = EnumName::EnumValue0;

```

### Structures
Class and struct members must be prefixed with `m`.
```cpp
struct MyStruct {
    int mMyValue;
};
```

Static class instances must be prefixed with `s`.
```cpp
class MyClass {
public:
    static MyClass* sInstance;

    inline MyClass* Instance() {
        return sInstance;
    }
};
```

To separate members, methods, and struct/enum definitions, use the `private`/`public`/`protected` keywords.
```cpp
class MyClass {
public:
    ENUM_CLASS(MyEnum,
        EnumValue0,
        EnumValue1,
    );

    struct MySubstructure {
        int mSubstructureValue;
    };  
public:
    MyClass();
    ~MyClass();

    void DoSomething();
private:
    int mMyValue;
    float mMyFloatValue;
};
```

Offsets (and optionally sizes if they are unclear) for fields should be commented.
```cpp
struct MyStruct {
    int mMyValue; // @ 0x0
    Structure mSomeStructure; // @ 0x4, size: 0x10
    float mMyFloatValue; // @ 0x14
}
```

If the size is known, write a comment.
```cpp
// size: 0x8
class MyStruct {
    int mMyValue; // @ 0x0
    int mMyOtherValue; // @ 0x4
};

// you can use size asserts, too
ASSERT_SIZE(MyStruct, 0x8);

...

// variable size
struct MyOtherStruct {
    int mCount;
    // int mValues[mCount];
};
```

Unknown fields will be referred to by their offset (in hex).
They don't need a comment.

```cpp
struct MyStruct {
    int mKnownValue; // @ 0x0
    int m_4;
    int m_8;
    int m_C;
    int mAnotherKnownValue; // @ 0x10
    int m_14;
    ...
};
```

Assume members of a class are `private`/`protected` and use inlined getters/setters (if such a function does not exist already). To avoid clutter, only add them when necessary.

```cpp
class MyClass {
public:
    // there is a function for this
    void SetValue(int value);

    inline int GetValue() {
        // there is not a function for this, so
        // an inlined function should be created
        return mValue;
    }

private:
    int mValue;
};
```

### Conditionals
Use `nullptr` in C++, use `NULL` in C.

Be explicit when checking if a pointer is `NULL`/`nullptr`.


```cpp
// bad
if (ptr) {
    ...
}

if (!ptr) {
    ...
}

// good
if (ptr != nullptr) {
    ...
}

if (ptr == NULL) {
    ...
}
```

### Literals
Be explicit for floating-point values.

```cpp
// bad
float myFloat = 1;
double myDouble = 2.;

// ok, but might cause issues depending on scenario
float myFloat = 1.0;
double myDouble = 2.0;

// good
float myFloat = 1.0f;
double myDouble = 2.0d;
```

### Files
Files for *Kirby's Epic Yarn* are in PascalCase.

Headers and C++ source files written by Good-Feel end in `.h` and `.cpp`.

```cpp
"MyHeader.hpp"  // bad
"myHeader.h"    // bad
"MyHeader.h"    // good

"MyCode.cc"     // bad
"MyCode.cxx"    // bad
"myCode.cpp"    // bad
"MyCode.cpp"    // good
```

Files for Good-Feel's *Good-Feel Library* (GFL) follow the same structure, but are prefixed with "gfl".

```cpp
"GFLRenderObj.h"    // bad
"RenderObj.h"       // bad
"gfl_RenderObj.h"   // bad
"gflRenderObj.h"    // good
```

Headers (`.h`) and source files (`.cpp`) go in the same folder.

Excluding the base folder, use the full file path when including headers.

```cpp
/* src/fluff/object/gimmick/GmkTurtle.cpp */

#include "GmkTurtle.h"                  // bad
#include "object/gimmick/GmkTurtle.h"   // good

#include "gflScopedPointer.h"           // bad
#include "gfl/gflScopedPointer.h"       // good

...

/* src/gfl/gflRenderObj.cpp */

#include "gflRenderObj.h"               // good
```

Libraries (excluding GFL) must be included with angle brackets.
```cpp
#include "nw4r/math.h" // bad
#include <nw4r/math.h> // good
```