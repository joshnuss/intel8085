#include "lexer.h"

Lexer::Lexer() : lineNumber(0) {
}

void Lexer::parse_line(string line) {
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

string Lexer::toString() {
  ostringstream result;

  for (list<Token>::iterator it= tokens.begin(); it != tokens.end(); it++) {
    result << (*it).toString() << endl;
  }

  return result.str();
}

void Lexer::addUnlessEmpty(unsigned int lineNumber, string& text) {
  if (!text.empty()) {
    tokens.push_back(Token(lineNumber, TEXT, text));
    text = "";
  }
}

list<Token> Lexer::getTokens() {
  return tokens;
}
