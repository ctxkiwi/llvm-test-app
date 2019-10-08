
#ifndef LEXER_H
#define LEXER_H

class Lexer {
 public:
  //
  std::string IdentifierStr;  // Filled in if tok_identifier
  double NumVal;              // Filled in if tok_number
  std::string code;
  unsigned long index = -1;
  int currentToken;

  // The lexer returns tokens [0-255] if it is an unknown character, otherwise
  // one of these for known things.
  enum Token {
    tok_eof = -1,

    // commands
    tok_def = -2,
    tok_extern = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,
  };

  int getNextToken();
  int getNextTokenReal();
  int getNextChar();
  int getCurrentToken();
  int getCurrentChar();
  Lexer();

};

#endif