#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>

using namespace std;
using namespace boost;

enum TokenType {
  UNKNOWN,
  LINE_START,
  LINE_END,
  WHITESPACE,
  COMMA,
  COLON,
  SEMICOLON,
  TEXT
};

class Token {
  private:
    string value;
    TokenType type;
    unsigned long lineNumber;

  private:
    void init(unsigned long lineNumber, TokenType type, string value);

  public: 
    Token(unsigned long lineNumber, TokenType type, string value);
    Token(unsigned long lineNumber, TokenType type);
    Token(unsigned long lineNumber);
    Token();
    string to_s();

    unsigned long getLineNumber();
    void setLineNumber(unsigned long value);

    TokenType getType();
    void setType(TokenType value);
    
    string getValue();
    void setValue(string val);
};

#endif // __TOKEN_H_
