
#include <iostream>
#include <cstring>
#include <string>

#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

#include "other.h"

llvm::LLVMContext mainContext;

int main(int argc, char *argv[]) {

  std::unique_ptr<llvm::Module> mainModule = llvm::make_unique<llvm::Module>("GG Program", mainContext);

  printf("%s", text());
  return 0;
}