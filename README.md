# cpp_hot_reloading

This repository is based on [this](https://www.youtube.com/watch?v=QAeRxfeFAo0) YouTube video by Cakez, explaining how to do C++ hot reloading.

## Running on Linux

1. `c++ update.cpp -std=c++17 -g -shared -fPIC -o update.dll`
2. `c++ main.cpp -std=c++17 -g -o program`
3. `./program`
4. Edit `update.cpp` and rerun step #1 to see the hot reloading

## Running on Windows using the Zig compiler

1. `zig c++ update.cpp -std=c++17 -g -shared -o update.dll`
2. `zig c++ main.cpp -std=c++17 -g -o program`
3. `./program`
4. Edit `update.cpp` and rerun step #1 to see the hot reloading
