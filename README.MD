# Cpp Features Dojo

This repository is for practicing C++ features.

## Requirements

- CMake
- GTest
- 

## How to build

```bash
# prepare build directory
mkdir build

# configure
cmake -S . -B ./build

# build
cmake --build ./build -- -j 10
```

## How to run

```bash
# run all testcases
./build/cppXXdojo

# run only testcases of cpp11
./build/cpp11dojo

# run only testcases of cpp17
./build/cpp17dojo

# run only testcases of cpp20
./build/cpp20dojo
```

## Compiler Compatibility

- GCC
    - [x] 13.2.0
