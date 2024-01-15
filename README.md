# cpp_hot_reloading

This repository is based on [this](https://www.youtube.com/watch?v=QAeRxfeFAo0) YouTube video by Cakez, explaining how to do C++ hot reloading.

## Running on Linux or Windows

1. `c++ update.cpp -g -shared -o update.dll`
2. `c++ main.cpp -g -o program`
3. `./program`

## Running on Windows using Zig

1. `zig c++ update.cpp -g -shared -o update.dll`
2. `zig c++ main.cpp -g -o program`
3. `./program`
