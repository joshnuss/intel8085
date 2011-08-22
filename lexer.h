#ifndef __LEXER_H__
#define __LEXER_H__

#include <string>
#include <list>

#include "token.h"

using namespace std;

class Lexer {
  private:
    unsigned long lineNumber;
    list<Token> tokens;

  public:
    Lexer();
    void parse_line(string line);
    string to_s();

  private:
    void addUnlessEmpty(unsigned int lineNumber, string& text);
};

#endif // __LEXER_H__
