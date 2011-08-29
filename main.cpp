#include "token.h"
#include "lexer.h"
#include "instruction.h"
#include "parser.h"

int main(int argc, char* argv[]) {
  /*
  Token token(1, LINE_START);

  cout << token.toString() << endl;

  token.setLineNumber(2);
  token.setType(TEXT);
  token.setValue("FOO");
  cout << token.toString() << endl;
  */

  Lexer lexer;
  lexer.parse_line("TEST:  MVI A,B ; BLA BLA BLA");
  lexer.parse_line("DAA");
  lexer.parse_line("JC a");
  lexer.parse_line("LXI D, nn");
  
  cout << lexer.toString();

  /*
  Instruction instruction("LXI");
  instruction.addParameter("R");
  instruction.addParameter("0xFF");

  cout << instruction.toString() << endl;

  Instruction instruction2("STOR");
  instruction2.setLabel("Main");
  instruction2.addParameter("W");
  instruction2.addParameter("X");

  cout << instruction2.toString() << endl;
  */

  Parser parser;
  parser.parse(lexer.getTokens());

  cout << parser.toString() << endl;
}
