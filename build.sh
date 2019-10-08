
time clang++ src/compiler/globals.cpp src/compiler/functions.cpp src/compiler/main.cpp src/compiler/lexer.cpp src/compiler/packageCompiler.cpp src/compiler/AST.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o bin/gg
time ./bin/gg run examples/basic/main.gg