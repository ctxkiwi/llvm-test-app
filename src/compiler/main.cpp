
#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "lexer.h"
#include "packageCompiler.h"

static llvm::LLVMContext mainContext;
static llvm::IRBuilder<> Builder(mainContext);
static std::unique_ptr<llvm::Module> mainModule;

bool fileExists (const std::string& name) {
  if (FILE *file = fopen(name.c_str(), "r")) {
    fclose(file);
    return true;
  }
  return false;
}

std::string fileGetContents(const std::string &name) {
  std::ifstream ifs(name.c_str());
  std::string content( (std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()) );
  return content;
}

int main(int argc, char *argv[]) {

  // Make the llvm module, which holds all the code.
  mainModule = llvm::make_unique<llvm::Module>("GG Program", mainContext);

  // Handle commandline args
  std::string compileFile;
  std::vector<std::string> commands;
  std::map<std::string, std::string> args; // e.g. '--say" => "hello", "--uppercase" => ""

  std::string prevArg;
  for (int i = 0; i < argc; ++i) {

    if(i == 0){ continue; }

    std::string arg = argv[i];
    if(arg.at(0) == '-'){
      // Param
      if(prevArg.empty()){
        args[arg] = "_";
      }
      prevArg = arg;
    }else{
      if(!prevArg.empty()){
        // Store as arg value
        args[prevArg] = arg;
        prevArg.clear();
        continue;
      }

      commands.push_back(arg);
    }
  }

  if(commands.size() > 0){

    if(commands[0] == "run"){
      if(commands.size() == 1){
        fprintf(stderr, "Missing file parameter for \"run\" commands\n");
        return 1;
      }

      compileFile = commands[1];
      if(!fileExists(compileFile)){
        fprintf(stderr, "Can't find file: %s\n", compileFile.c_str());
        return 1;
      }

      char * path = new char[compileFile.length() + 1];
      strcpy(path, compileFile.c_str());
      char * part;
      part = std::strtok(path, "/");
      std::string directory = "";
      std::string file;
      while (part != NULL) {
        if(!file.empty()){
          directory = directory + file + "/";
        }
        file = part;
        // printf("%s\n", part);
        part = std::strtok(NULL, "/");
      }

      printf("Filename: %s\n", file.c_str());
      printf("Dir: %s\n", directory.c_str());

      PackageCompiler* pkgCompiler = PackageCompiler::create(directory);
      pkgCompiler->compileFile(file);
    }
  }

  // Print out IR code
  mainModule->print(llvm::errs(), nullptr);

  // Return success
  return 0;
}
