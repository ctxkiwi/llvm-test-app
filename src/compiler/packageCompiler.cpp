
#include <vector>
#include <set>

#include "lexer.h"
#include "functions.h"
#include "packageCompiler.h"

PackageCompiler* PackageCompiler::create(std::string rootDir){
  PackageCompiler* pc = new PackageCompiler();
  pc->lexer = new Lexer();
  pc->directory = rootDir;
  return pc;
}

void PackageCompiler::loadFile(std::string file){

  auto path = directory + file;

  if (compiledFiles.find(path) != compiledFiles.end()){
    return;
  }
  compiledFiles.insert(path);

  if(!fileExists(path)){
    printf("File not found: %s", path.c_str());
    exit (EXIT_FAILURE);
  }

  std::string newCode = fileGetContents(path);
  lexer->code += "\n" + newCode;

}

void PackageCompiler::compileFile(std::string file){

  loadFile(file);

}