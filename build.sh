
time clang++ src/compiler/globals.cpp src/compiler/main.cpp src/compiler/lexer.cpp src/compiler/packageCompiler.cpp src/compiler/AST.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o build/gg
time ./build/gg run examples/basic/main.gg