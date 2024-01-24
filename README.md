# cpp_hot_reloading

https://github.com/MyNameIsTrez/cpp_hot_reloading/assets/32989873/ce976ca7-7221-4406-8ba4-3b56e406c3ff

This repository is based on [this](https://www.youtube.com/watch?v=QAeRxfeFAo0) YouTube video by Cakez, explaining how to do C++ hot reloading. It works on both Windows and Linux.

## Running

1. `c++ src/inner/update2.cpp src/update.cpp -std=c++17 -I . -g -shared -fPIC -o program_tmp.dll && mv program_tmp.dll program.dll`
2. `c++ main.cpp reload_dll.cpp -std=c++17 -g -o program && ./program`
3. Edit `src/inner/update2.cpp` (or any other file in `src/`) and rerun step #1 to see the hot reloading in action!

## Running with no DLL

You can disable hot reloading, compiling everything into one executable like normal, with `-D NO_DLL`:

`c++ main.cpp src/inner/update2.cpp src/update.cpp -std=c++17 -I . -g -D NO_DLL -o program && ./program`

## Running with Zig's compiler

If you're on Windows, you might want to install [Zig's compiler](https://ziglang.org/) so you can run these commands with `zig c++`.

## Stepping into the DLL's code with GDB

Stepping into the DLL's code works out of the box, but if you make any changes to the DLL's code, you'll need to run `directory` and then answer "Reinitialize source path to empty?" with `y` in order to have GDB reload the changed files.

## Compiling with GCC

You'll need to compile with `-fno-gnu-unique` in order for `dlclose()` to do something on GCC.

The [`-fno-gnu-unique`](https://gcc.gnu.org/onlinedocs/gcc-9.1.0/gcc/Code-Gen-Options.html) option's documentation states (where DSO stands for Dynamic Shared Object):

> But this causes dlclose to be ignored for affected DSOs; if your program relies on reinitialization of a DSO via dlclose and dlopen, you can use -fno-gnu-unique.

Further discussion can be found at [this](https://stackoverflow.com/a/51402034/13279557) Stack Overflow answer.