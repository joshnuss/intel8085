#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>

#include "token.h"

using namespace std;

/*
class Lexer {
  private:
    unsigned long lineNumber;
    list<Token> tokens;

  public:
    Lexer() : lineNumber(0) {
    }

    void parse_line(string line) {
      Token token;
      token.setLineNumber(++lineNumber);

      int index = line.find(':');
      string rest = line;

      if (index > 0) {
        string label = line.substr(0, index);
        trim(label);
        token.setLabel(label);
        rest = line.substr(index+1);
      }
      trim(rest);

      index = rest.find(' ');
      string operation;
      if (index > 0) {
        operation = rest.substr(0, index);
        rest = rest.substr(index+1);
      }
      else {
        operation = rest;
        rest = "";
      }

      if (!operation.empty()) {
        trim(operation);
        token.setOperation(operation);

        if (!rest.empty()) {
          vector<string> SplitVec;
          split(SplitVec, rest, is_any_of(","), token_compress_on );

          for (vector<string>::iterator it=SplitVec.begin(); it != SplitVec.end(); it++) {
            trim(*it);
            token.addParameter(*it);
          }
        }
      }

      tokens.push_back(token);
    }

    string to_s() {
      ostringstream result;

      for (list<Token>::iterator it= tokens.begin(); it != tokens.end(); it++) {
        result << (*it).to_s() << endl;
      }

      return result.str();
    }
};
*/

int main(int argc, char* argv[]) {
  Token token(1, LINE_START);

  cout << token.to_s() << endl;

  token.setLineNumber(2);
  token.setType(TEXT);
  token.setValue("FOO");
  cout << token.to_s() << endl;

  /*
  Lexer lexer;
  lexer.parse_line("TEST: MVI A,B");
  lexer.parse_line("DAA");
  lexer.parse_line("JC a");
  lexer.parse_line("LXI D, nn");
  
  cout << lexer.to_s();
  */
}
