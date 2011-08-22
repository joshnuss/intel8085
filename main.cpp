#include <iostream>

#include "token.h"
#include "lexer.h"

using namespace std;

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
