
#include "lexer.h"
#include "packageCompiler.h"

PackageCompiler* PackageCompiler::create(std::string rootDir){
  PackageCompiler* pc = new PackageCompiler();
  return pc;
}
