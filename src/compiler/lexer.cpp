
#include "lexer.h"

double Lexer::NumVal;
std::string Lexer::IdentifierStr; 

// Gettok - Return the next token from standard input.
int Lexer::getToken() {
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar)) LastChar = getchar();

  if (isalpha(LastChar)) {  // identifier: [a-zA-Z][a-zA-Z0-9]*
    Lexer::IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar()))) Lexer::IdentifierStr += LastChar;

    if (Lexer::IdentifierStr == "def") return Lexer::tok_def;
    if (Lexer::IdentifierStr == "extern") return Lexer::tok_extern;
    return Lexer::tok_identifier;
  }
  if (isdigit(LastChar) || LastChar == '.') {  // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    Lexer::NumVal = strtod(NumStr.c_str(), 0);
    return Lexer::tok_number;
  }
  if (LastChar == '#') {
    // Comment until end of line.
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF) return Lexer::getToken();
  }
  // Check for end of file.  Don't eat the EOF.
  if (LastChar == EOF) return Lexer::tok_eof;

  // Otherwise, just return the character as its ascii value.
  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}
