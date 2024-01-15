# cpp_hot_reloading

This repository is based on [this](https://www.youtube.com/watch?v=QAeRxfeFAo0) YouTube video by Cakez, explaining how to do C++ hot reloading.

## Running on Linux or Windows

`c++ main.cpp -g -o program`
`c++ update.cpp -g -shared -o update.dll`

## Running on my shitty Windows that has a broken MINGW

My `c++` failed due to `std::filesystem::copy()` crashing the program, so I used Zig's compiler:

`zig c++ main.cpp -g -o program`
`zig c++ update.cpp -g -shared -o update.dll`
