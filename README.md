# cpp_hot_reloading

This repository is based on [this](https://www.youtube.com/watch?v=QAeRxfeFAo0) YouTube video by Cakez, explaining how to do C++ hot reloading.

## Running

1. `c++ src/**/*.cpp -std=c++17 -I. -g -shared -fPIC -o program_tmp.dll && mv program_tmp.dll program.dll`
2. `c++ main.cpp reload_dll.cpp -std=c++17 -g -o program && ./program`
3. Edit `src/inner/update2.cpp` and rerun step #1 to see the hot reloading in action!

## Running with Zig's compiler

1. `zig c++ src/**/*.cpp -std=c++17 -I. -g -shared -o program_tmp.dll && mv program_tmp.dll program.dll`
2. `zig c++ main.cpp reload_dll.cpp -std=c++17 -g -o program && ./program`
3. Edit `src/inner/update2.cpp` and rerun step #1 to see the hot reloading in action!
