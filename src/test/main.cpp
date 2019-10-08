
#include <iostream>
#include <cstring>
#include <string>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

#include "other.h"
#include "globals.h"

llvm::LLVMContext mainContext;

int main(int argc, char *argv[]) {

  mainModule = llvm::make_unique<llvm::Module>("GG Program", mainContext);

  printf("%s", text());
  return 0;
}