#include "token.h"

Token::Token(unsigned long lineNumber, TokenType type, string value) {
  init(lineNumber, type, value);
}

Token::Token(unsigned long lineNumber, TokenType type) {
  init(lineNumber, type, "");
}

Token::Token(unsigned long lineNumber) {
  init(lineNumber, UNKNOWN, "");
}

Token::Token() {
  init(0, UNKNOWN, "");
}

string Token::toString() {
  ostringstream result;

  result.width(8);
  result << right << lineNumber << " \t[";

  string typeStr = "";
  switch(type) {
    case LINE_START:
      typeStr = "LINE_START";
      break;
    case LINE_END:
      typeStr = "LINE_END";
      break;
    case WHITESPACE:
      typeStr = "WHITESPACE";
      break;
    case COMMA:
      typeStr = "COMMA";
      break;
    case SEMICOLON:
      typeStr = "SEMICOLON";
      break;
    case COLON:
      typeStr = "COLON";
      break;
    case TEXT:
      typeStr = "TEXT";
      break;
    default:
      typeStr = "??";
      break;
  }

  result << typeStr;

  if (!value.empty()) {
    result << ", " << value;
  }
    
  result << "]";

  return result.str();
}

unsigned long Token::getLineNumber() {
  return lineNumber;
}

void Token::setLineNumber(unsigned long value) {
  lineNumber = value;
}

TokenType Token::getType() {
  return type;
}

void Token::setType(TokenType value) {
  type = value;
}

string Token::getValue() {
  return value;
}

void Token::setValue(string val) {
  value = val;
}

void Token::init(unsigned long lineNumber, TokenType type, string value) {
  this->lineNumber = lineNumber;
  this->type = type;
  this->value = value;
}
