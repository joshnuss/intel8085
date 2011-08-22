#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>

#include "token.h"

using namespace std;
using namespace boost;

class Lexer {
  private:
    unsigned long lineNumber;
    list<Token> tokens;

  public:
    Lexer() : lineNumber(0) {
    }

    void parse_line(string line) {
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

    string to_s() {
      ostringstream result;

      for (list<Token>::iterator it= tokens.begin(); it != tokens.end(); it++) {
        result << (*it).to_s() << endl;
      }

      return result.str();
    }

  private:
    void addUnlessEmpty(unsigned int lineNumber, string& text) {
      if (!text.empty()) {
        tokens.push_back(Token(lineNumber, TEXT, text));
        text = "";
      }
    }
};

int main(int argc, char* argv[]) {
  /*
  Token token(1, LINE_START);

  cout << token.to_s() << endl;

  token.setLineNumber(2);
  token.setType(TEXT);
  token.setValue("FOO");
  cout << token.to_s() << endl;
  */

  Lexer lexer;
  lexer.parse_line("TEST:  MVI A,B ; BLA BLA BLA");
  lexer.parse_line("DAA");
  lexer.parse_line("JC a");
  lexer.parse_line("LXI D, nn");
  
  cout << lexer.to_s();
}
