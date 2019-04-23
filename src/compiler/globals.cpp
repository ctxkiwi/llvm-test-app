
#include "globals.h"

llvm::LLVMContext mainContext;
llvm::IRBuilder<> Builder(mainContext);
std::unique_ptr<llvm::Module> mainModule;
