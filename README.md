# cpp_hot_reloading

https://github.com/MyNameIsTrez/cpp_hot_reloading/assets/32989873/ce976ca7-7221-4406-8ba4-3b56e406c3ff

This repository is based on [this](https://www.youtube.com/watch?v=QAeRxfeFAo0) YouTube video by Cakez, explaining how to do C++ hot reloading. It works on both Windows and Linux.

## Running

1. `c++ src/inner/update2.cpp src/init.cpp src/init2.cpp src/update.cpp -std=c++17 -I . -g -shared -fPIC -o program_tmp.dll && mv program_tmp.dll program.dll`
2. `c++ main.cpp reload_dll.cpp -std=c++17 -g -o program && ./program`
3. Edit `src/inner/update2.cpp` (or any other file in `src/`) and rerun step #1 to see the hot reloading in action!

## Running with no DLL

You can disable hot reloading, compiling everything into one executable like normal, with `-D NO_DLL`:

`c++ main.cpp src/inner/update2.cpp src/init.cpp src/init2.cpp src/update.cpp -std=c++17 -I . -g -D NO_DLL -o program && ./program`

## Running with Zig's compiler

If you're on Windows, you might want to install [Zig's compiler](https://ziglang.org/) so you can run these commands with `zig c++`.
