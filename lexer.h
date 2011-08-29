#ifndef __LEXER_H__
#define __LEXER_H__

#include "token.h"

class Lexer {
  private:
    unsigned long lineNumber;
    list<Token> tokens;

  public:
    Lexer();
    void parse_line(string line);
    string toString();
    list<Token> getTokens();

  private:
    void addUnlessEmpty(unsigned int lineNumber, string& text);
};

#endif // __LEXER_H__
