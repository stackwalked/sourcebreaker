```
sourcebreaker
---
projects:
- mapper        -> multimodal dynamic library loader
- memtools      -> Win32 PE abstractions
- sourcebreaker -> primary target; shared library mapped into games
- tfsdk         -> Team Fortress 2 game SDK

toolchain:
- requires jetbrains clion for 1:1 reproduction (using Ninja gen.)
- build can be done using latest CMake by self-bootstrapping cmkr
- other IDE support untested

- cxx_std_23
- x64 only
- VS2022 / MSVCv143
- other build tools untested

~ stackwalked/2025
```