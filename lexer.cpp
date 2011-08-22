#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>

#include "lexer.h"

using namespace boost;

Lexer::Lexer() : lineNumber(0) {
}

void Lexer::parse_line(string line) {
  cout << line << endl;
  lineNumber++;

  tokens.push_back(Token(lineNumber, LINE_START));

  TokenType type = UNKNOWN;
  string text = "";

  string::iterator it;
  for ( it=line.begin(); it < line.end(); it++ ) {
    switch(*it) {
      case ',':
        addUnlessEmpty(lineNumber, text);
        tokens.push_back(Token(lineNumber, COMMA));
        break;
      case ':':
        addUnlessEmpty(lineNumber, text);
        tokens.push_back(Token(lineNumber, COLON));
        break;
      case ';':
        addUnlessEmpty(lineNumber, text);
        tokens.push_back(Token(lineNumber, SEMICOLON));
        break;
      case ' ':
      case '\t':
        addUnlessEmpty(lineNumber, text);
        if (tokens.back().getType() != WHITESPACE)
          tokens.push_back(Token(lineNumber, WHITESPACE));
        break;
      default:
        text += *it;
        break;

    }
  }

  addUnlessEmpty(lineNumber, text);
  tokens.push_back(Token(lineNumber, LINE_END));
}

string Lexer::to_s() {
  ostringstream result;

  for (list<Token>::iterator it= tokens.begin(); it != tokens.end(); it++) {
    result << (*it).to_s() << endl;
  }

  return result.str();
}

void Lexer::addUnlessEmpty(unsigned int lineNumber, string& text) {
  if (!text.empty()) {
    tokens.push_back(Token(lineNumber, TEXT, text));
    text = "";
  }
}