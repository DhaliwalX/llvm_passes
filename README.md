# Simple LLVM passes for learning purpose

### Building a pass X

```bash
cd X
mkdir build
cd build
cmake ..
make
```

### Running a pass X

opt -load libX.so -x a.ll

where x is the command line option which can be found in X.cc.