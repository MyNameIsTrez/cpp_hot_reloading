# cpp_hot_reloading

This repository is based on [this](https://www.youtube.com/watch?v=QAeRxfeFAo0) YouTube video by Cakez, explaining how to do C++ hot reloading.

## Running on Linux or Windows

`c++ update.cpp -g -shared -o update.dll`
`c++ main.cpp -g -o program`
`./program`

## Running on Windows using Zig

`zig c++ update.cpp -g -shared -o update.dll`
`zig c++ main.cpp -g -o program`
`./program`
