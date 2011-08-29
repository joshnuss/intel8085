#ifndef __PARSER_H__
#define __PARSER_H__

#include "iasm.h"
#include "instruction.h"
#include "token.h"

class Parser {
  private:
    list<Instruction> instructions;
    string text;
    string label;
    string operation;
    list<string> parameters;
    bool comment;
    Token token;

  public:
    Parser();
    void parse(list<Token> tokens);
    string toString();

  private:
    void parseLineStart();
    void parseSemicolon();
    void parseComma();
    void parseText();
    void parseWhitespace();
    void parseColon();
    void parseLineEnd();
};

#endif // __PARSER_H__
