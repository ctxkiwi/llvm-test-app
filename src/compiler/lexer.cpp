
#include "lexer.h"

Lexer::Lexer(){
  code = "";
}

// getToken - Return the next token
int Lexer::getNextToken() {
  currentToken = getNextToken();
  return currentToken;
}

int Lexer::getNextTokenReal() {
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar)){
    LastChar = getNextChar();
  }

  if (isalpha(LastChar)) {  // identifier: [a-zA-Z][a-zA-Z0-9]*
    Lexer::IdentifierStr = LastChar;
    while (isalnum((LastChar = getNextChar()))) Lexer::IdentifierStr += LastChar;

    if (Lexer::IdentifierStr == "def") return Lexer::tok_def;
    if (Lexer::IdentifierStr == "extern") return Lexer::tok_extern;
    return Lexer::tok_identifier;
  }
  if (isdigit(LastChar) || LastChar == '.') {  // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getNextChar();
    } while (isdigit(LastChar) || LastChar == '.');

    Lexer::NumVal = strtod(NumStr.c_str(), 0);
    return Lexer::tok_number;
  }
  if (LastChar == '#') {
    // Comment until end of line.
    do {
      // LastChar = getchar();
      LastChar = getNextChar();
    } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF) return Lexer::getNextToken();
  }
  // Check for end of file.  Don't eat the EOF.
  if (LastChar == EOF) return Lexer::tok_eof;

  // Otherwise, just return the character as its ascii value.
  int ThisChar = LastChar;
  // LastChar = getchar();
  LastChar = getNextChar();
  return ThisChar;
}

int Lexer::getNextChar(){
  index++;
  if(index >= code.length()){
    return EOF;
  }
  return code[index];
}

int Lexer::getCurrentChar(){
  if(index >= code.length()){
    return EOF;
  }
  return code[index];
}
