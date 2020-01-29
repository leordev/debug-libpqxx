# How to reproduce the project

```
# clone this repo
git submodule update --init --recursive
mkdir -p build/run && cd build/run
cmake ../..
make -j
./src/divider
```

# CMake C++ Project Template

This project was built based on this template: https://github.com/kigster/cmake-project-template
