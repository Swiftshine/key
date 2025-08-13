# Contributing
If you have questions or are interested in contributing, consider asking in the [GC/Wii Decompilation Discord](https://discord.gg/hKx3FJJgrV) in the `#kirbys-epic-yarn` channel.

Sections:
- [Resources](#resources)
- [Code style](#code-style)
    - [General](#general)
    - [Headers](#headers)
    - [Files and includes](#files-and-includes)
    - [Function signatures](#function-signatures)
    - [Function parameters](#function-parameters)
    - [Function contents](#function-contents)
    - [Enums](#enums)
    - [Structures](#structures)
    - [Literals](#literals)

## Resources
- [Ghidra](https://ghidra-sre.org/) - A disassembling, decompiling, and reverse-engineering tool.
    - Using these [custom Ghidra builds](https://github.com/encounter/ghidra-ci/releases) is recommended.
    - Access to the shared Ghidra project for *Kirby's Epic Yarn* (and other Good-Feel titles) can be requested in the `#ghidra` channel in the [GC/Wii Decompilation Discord](https://discord.gg/hKx3FJJgrV).
- [Objdiff](https://github.com/encounter/objdiff) - A local diffing tool.

## Code style
### General
Lines should not exceed `100` characters. These can be split into multiple lines.

Use `nullptr` instead of `0` when assigning or comparing a pointer in C++.
Likewise, use `NULL` in C.
- Be explicit when comparing pointers.
    ```cpp
    // bad
    if (ptr) { }

    // good
    if (ptr != nullptr) { }
    if (ptr != NULL) { }
    ```

### Headers
Use forward declared types when possible.

Use proper header guards.
```cpp
#ifndef FLUFF_MYHEADER_H
#define FLUFF_MYHEADER_H
// ...
#endif
```

### Files and includes
For SDK or STL includes, use angled brackets. For game or GFL includes, use quotation marks.

Relative to the source folder, use the full path to a header.
```cpp
/* src/fluff/object/gimmick/GmkTurtle.cpp */

#include "GmkTurtle.h"                  // bad
#include "object/gimmick/GmkTurtle.h"   // good
```

Use PascalCase when naming files for game code.

For GFL, do the same, but prefixed with "gfl". e.g. `gflRenderObj.h` instead of `RenderObj.h`

### Function signatures
No known Good-Feel title was shipped with debug symbols. However, many Good-Feel titles are compiled with [RTTI](https://en.wikipedia.org/wiki/Run-time_type_information). Therefore, all symbol names must be inferred from RTTI or from what the function does.

Function names written by Good-Feel in *Kirby's Epic Yarn* are known to be named with PascalCase.
To mimic Good-Feel's own programming, functions in this decompilation will, too.

Unknown virtual functions are to be named based on their offset relative to the start of the [virtual table](https://en.wikipedia.org/wiki/Virtual_method_table), prefixed with "vf".

```cpp
class MyClass {
public:
    /* 0x08 */ virtual void KnownFunction();
    /* 0x0C */ virtual void vfC(); 
    /* 0x10 */ virtual void vf10();
    /* 0x14 */ virtual void AnotherKnownFunction();
    /* 0x18 */ virtual void vf18();
};
```
### Function Parameters
Function arguments should have certain prefixes if applicable:
- `p` for pointers
- `r` for values passed by reference

### Function contents
Functions that don't require code to be written, i.e. a `void` function that does nothing, should have the `return` keyword for the sake of clarity.
Empty destructors should only take up one line.

```cpp
void DoesNothing() {
    return;
}

Structure::~Structure() { }
```

If a function is not 100% matching, leave a comment above the function with a link to the associated [decomp.me](https://decomp.me) scratch. Remove it once the function has been matched.

```cpp
// Nonmatching: https://decomp.me/scratch/EXAMPLE
void MyClass::SomeFunction() {
    ...
}
```

### Enums
C++98/03 does not allow you to refer to an enum by the name of its enumeration. To get around this, use the `ENUM_CLASS` macro.
```cpp
ENUM_CLASS(EnumName,
    EnumValue0 = 0,
    EnumValue1 = 1,
    ...
);

int x = EnumName::EnumValue0;
```

### Structures
- Class and struct members must be prefixed with `m`.
- Static class instances must be prefixed with `s`.

For the purpose of making decompilation easier, assume all class methods and member fields on a class are public.

Data entered into a class definition must be placed in the following order:
- enum and structure definitions
- `static` variables
- constructor
- destructor*
- virtual functions
- operators
- member functions
- static functions
- member variables

\* If the destructor is `virtual`, place it with the other virtual functions according to its position in the vtable.
E.g. if the destructor is the last function in the vtable, place it last in the
virtual function section.

Give descriptions of structures if appropriate. Provide a comment describing its size.
If the size is variable, indicate so.

Offsets for fields and virtual functions relative to the start of the structure and
the start of the vtable respectively must be commented.

```cpp
/// @brief This does something.
/// @note Size: `0x8`
class MyClass {
public:
    ENUM_CLASS(MyEnum,
        EnumValue0,
        EnumValue1,
    );

    struct MySubstructure {
        int mSubstructureValue;
    };  

    MyClass();
    ~MyClass();

    /* 0x8 */ virtual void DoSomething();

    void DoSomethingElse();

    /* 0x4 */ int mMyValue; ///< When leaving comments on fields, be concise.
    /* 0x8 */ float mMyFloatValue; ///< Indicates something.
};
```

Unknown fields must be referred to by their offset in hex, prefixed by an underscore.
```cpp
struct MyStruct {
    /* 0x00 */ int mKnownValue;
    /* 0x04 */ int m_4;
    /* 0x08 */ int m_8;
    /* 0x0C */ int m_C;
    /* 0x10 */ int mAnotherKnownValue;
    /* 0x14 */ int m_14;
    ...
};
```

Avoid using inline functions to get or set a value unless it's known that such a function is inline or if it must be used to match a function.

### Literals
Be explicit for floating-point values.

```cpp
// bad
float myFloat = 1;
double myDouble = 2.;

// bad
float myFloat = 1.0; // `1.0` is implicitly a double value, not a float.

// good
float myFloat = 1.0f;
double myDouble = 2.0;
```
