
#ifndef GLOBALS_H
#define GLOBALS_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

extern llvm::LLVMContext mainContext;
extern llvm::IRBuilder<> Builder;
extern std::unique_ptr<llvm::Module> mainModule;

#endif
