# Build & Run unit tests

Ensure you have gcc or any c++ compiler added into your system path. Then, run the following commands:

```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
make -j8
ctest
```

