# cpp_hot_reloading

This repository is based on [this](https://www.youtube.com/watch?v=QAeRxfeFAo0) YouTube video by Cakez, explaining how to do C++ hot reloading.

## Running

1. `c++ src/inner/update2.cpp src/init.cpp src/init2.cpp src/update.cpp -std=c++17 -I . -g -shared -fPIC -o program_tmp.dll && mv program_tmp.dll program.dll`
2. `c++ main.cpp reload_dll.cpp -std=c++17 -g -o program && ./program`
3. Edit `src/inner/update2.cpp` and rerun step #1 to see the hot reloading in action!

## Running with no DLL

You can disable a DLL being used by compiling with `-D NO_DLL`:

`c++ main.cpp src/inner/update2.cpp src/init.cpp src/init2.cpp src/update.cpp -std=c++17 -I . -g -D NO_DLL -o program && ./program`

## Running with Zig's compiler

It's also possible to compile with `zig c++`, rather than `c++`.
