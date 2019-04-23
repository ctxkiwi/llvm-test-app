
#ifndef PACKAGE_C_H
#define PACKAGE_C_H

#include <map>
#include <vector>
#include <set>

#include "AST.h"

class PackageCompiler {

 public:

  // Functions
  static PackageCompiler* create(std::string rootDir);

  void compileFile(std::string file);
  void loadFile(std::string file);
  void parseCode();
  void handleTopLevelExpr();

  std::unique_ptr<FunctionAST> parseTopLevelExpr();
  std::unique_ptr<ExprAST> parseExpression();
  std::unique_ptr<ExprAST> parsePrimary();
  std::unique_ptr<ExprAST> parseNumberExpr();
  std::unique_ptr<ExprAST> parseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS);

  static std::map<char, int> binopPrecedence;
  int getTokenPrecedence();

 private:

 // Vars
  std::map<std::string, PackageCompiler> subPkgCompilers;
  std::string directory;
  Lexer* lexer;
  std::vector<std::string> compileFiles;
  std::set<std::string> compiledFiles;
  bool parsing = false;

};

#endif
