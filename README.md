# WiZard

ssh:

    git clone --recurse-submodules git@github.com:xTarzx/wizardpp.git

https:

    git clone --recurse-submodules https://github.com/xTarzx/wizardpp.git

### Linux

    mkdir build
    cmake . -B build
    cmake --build build

### Windows -- MinGW

    mkdir build
    cmake . -B build -G "MinGW Makefiles"
    cmake --build build

above can be applied to all modules in "extern"
