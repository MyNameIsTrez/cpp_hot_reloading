# cpp_hot_reloading

This repository is based on [this](https://www.youtube.com/watch?v=QAeRxfeFAo0) YouTube video by Cakez, explaining how to do C++ hot reloading.

## Running

1. `c++ src/update.cpp -std=c++17 -g -shared -fPIC -o dll/update_tmp.dll && mv dll/update_tmp.dll dll/update.dll`
2. `c++ main.cpp -std=c++17 -g -o program && ./program`
3. Edit `update.cpp` and rerun step #1 to see the hot reloading in action!

## Running with Zig's compiler

1. `zig c++ src/update.cpp -std=c++17 -g -shared -o dll/update_tmp.dll && mv dll/update_tmp.dll dll/update.dll`
2. `zig c++ main.cpp -std=c++17 -g -o program && ./program`
3. Edit `update.cpp` and rerun step #1 to see the hot reloading in action!
