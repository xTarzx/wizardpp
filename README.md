# WiZard

## Cloning

### https:

    git clone --recurse-submodules https://github.com/xTarzx/wizardpp.git

might wanna do this one:

    git clone --recurse-submodules --shallow-submodules https://github.com/xTarzx/wizardpp.git

### ssh:

    git clone --recurse-submodules git@github.com:xTarzx/wizardpp.git

might wanna do this one:

    git clone --recurse-submodules --shallow-submodules git@github.com:xTarzx/wizardpp.git

## Compilation

### Linux

    mkdir build
    cmake . -B build
    cmake --build build

### Windows -- MinGW

    mkdir build
    cmake . -B build -G "MinGW Makefiles"
    cmake --build build

above can be applied to all modules in "extern"
