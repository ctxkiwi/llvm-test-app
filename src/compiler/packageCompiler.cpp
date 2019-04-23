
#include <memory>
#include <vector>
#include <set>

#include "llvm/ADT/STLExtras.h"

#include "lexer.h"
#include "functions.h"
#include "packageCompiler.h"

std::map<char, int> PackageCompiler::binopPrecedence = {
    {'<', 10},
    {'+', 20},
    {'-', 20},
    {'*', 40},
};

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

  if(parsing){
    return;
  }

  parseCode();

}

void PackageCompiler::compileFile(std::string file){

  loadFile(file);

}

void PackageCompiler::parseCode(){

  int curToken;

  while (true) {

    curToken = lexer->getNextToken();
    // printf("Tkn: %d", curToken);

    switch (curToken) {
      case Lexer::tok_eof:
        return;
      case ';':  // ignore top-level semicolons.
        lexer->getNextToken();
        break;
      case Lexer::tok_def:
        // HandleDefinition();
        break;
      case Lexer::tok_extern:
        // HandleExtern();
        break;
      default:
        handleTopLevelExpr();
        break;
    }
  }
}

void PackageCompiler::handleTopLevelExpr() {
  // Evaluate a top-level expression into an anonymous function.
  if (auto FnAST = parseTopLevelExpr()) {
    if (auto *FnIR = FnAST->codegen()) {
      fprintf(stderr, "Read top-level expression:");
      FnIR->print(llvm::errs());
      fprintf(stderr, "\n");
    }
  } else {
    // Skip token for error recovery.
    lexer->getNextToken();
  }
}

std::unique_ptr<FunctionAST> PackageCompiler::parseTopLevelExpr() {
  if (auto E = parseExpression()) {
    // Make an anonymous proto.
    auto Proto = llvm::make_unique<PrototypeAST>("__anon_expr", std::vector<std::string>());
    return llvm::make_unique<FunctionAST>(std::move(Proto), std::move(E));
  }
  return nullptr;
}

std::unique_ptr<ExprAST> PackageCompiler::parseExpression() {
  auto LHS = parsePrimary();
  if (!LHS)
    return nullptr;

  return parseBinOpRHS(0, std::move(LHS));
}

std::unique_ptr<ExprAST> PackageCompiler::parsePrimary() {
  switch (lexer->currentToken) {
  case Lexer::tok_identifier:
    // return ParseIdentifierExpr();
  case Lexer::tok_number:
    return parseNumberExpr();
  case '(':
    // return ParseParenExpr();
  default:
    printf("unknown token when expecting an expression");
    exit (EXIT_FAILURE);
  }
}

std::unique_ptr<ExprAST> PackageCompiler::parseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
  // If this is a binop, find its precedence.
  while (true) {
    int TokPrec = getTokenPrecedence();

    // If this is a binop that binds at least as tightly as the current binop,
    // consume it, otherwise we are done.
    if (TokPrec < ExprPrec)
      return LHS;

    // Okay, we know this is a binop.
    int BinOp = lexer->currentToken;
    lexer->getNextToken(); // eat binop

    // Parse the primary expression after the binary operator.
    auto RHS = parsePrimary();
    if (!RHS)
      return nullptr;

    // If BinOp binds less tightly with RHS than the operator after RHS, let
    // the pending operator take RHS as its LHS.
    int NextPrec = getTokenPrecedence();
    if (TokPrec < NextPrec) {
      RHS = parseBinOpRHS(TokPrec + 1, std::move(RHS));
      if (!RHS)
        return nullptr;
    }

    // Merge LHS/RHS.
    LHS = llvm::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
  }
}

int PackageCompiler::getTokenPrecedence() {
  if (!isascii(lexer->currentToken))
    return -1;

  // Make sure it's a declared binop.
  int TokPrec = binopPrecedence[lexer->currentToken];
  if (TokPrec <= 0)
    return -1;
  return TokPrec;
}

// numberexpr ::= number
std::unique_ptr<ExprAST> PackageCompiler::parseNumberExpr() {
  auto Result = llvm::make_unique<NumberExprAST>(lexer->NumVal);
  lexer->getNextToken(); // consume the number
  return std::move(Result);
}

