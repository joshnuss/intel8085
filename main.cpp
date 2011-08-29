#include <iostream>

#include "token.h"
#include "lexer.h"

#include <list>

using namespace std;

class Instruction {
  private:
    string label;
    string operation;
    list<string> parameters;

  public:
    Instruction() {
      init("");
    }
    
    Instruction(string operation) {
      init(operation);
    }

    string toString() {
      stringstream result;

      if (!label.empty()) {
        result << label << ":" << endl;
      }

      result << "\t" << operation;

      if (parameters.size() > 0) {
        result << " ";

        int count = 0;
        for (list<string>::iterator it=parameters.begin(); it != parameters.end(); it++, count++) {
          result << *it;

          if (count < parameters.size()-1)
            result << ", ";
        }
      }

      return result.str();
    }

    void addParameter(string val) {
      parameters.push_back(val);
    }

    string getOperation() {
      return operation;
    }

    void setOperation(string value) {
      operation = value;
    }

    string getLabel() {
      return label;
    }

    void setLabel(string value) {
      label = value;
    }
  private:
    void init(string operation) {
      this->operation = operation;
      label = "";
    }
};

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
    Parser() {
      text = "";
      label = "";
      operation = "";
      comment = false;
    }

    void parse(list<Token> tokens) {
      for (list<Token>::iterator it=tokens.begin(); it != tokens.end(); it++) {
        token = *it;
        TokenType type = token.getType();

        if (comment && type != LINE_END) continue;

        switch(type) {
          case SEMICOLON:
            parseSemicolon();
            break;

          case LINE_START:
            parseLineStart();
            break;

          case LINE_END:
            parseLineEnd();
            break;
            
          case COLON:
            parseColon();
            break;

          case WHITESPACE:
            parseWhitespace();
            break;

          case COMMA:
            parseComma();
            break;

          case TEXT:
            parseText();
            break;
        }
      }
    }

    string toString() {
      stringstream result;
      
      for (list<Instruction>::iterator it=instructions.begin(); it != instructions.end(); it++) {
        result << it->toString() << endl;
      }

      return result.str();
    }

  private:
    void parseLineStart() {
      label = "";
      text = "";
      operation = "";
      parameters.clear();
    }

    void parseSemicolon() {
      comment = true;
    }

    void parseComma() {
      if (!text.empty()) {
        parameters.push_back(text);
        text = "";
      }
    }

    void parseText() {
      text = token.getValue();
    }

    void parseWhitespace() {
      if (!text.empty()) {
        if (operation.empty()) 
          operation = text;
        else 
          parameters.push_back(text);

        text = "";
      }
    }

    void parseColon() {
      label = text;
      text = "";
    }

    void parseLineEnd() {
      if (!text.empty()) {
        if (operation.empty()) 
          operation = text;
        else 
          parameters.push_back(text);

        text = "";
      }
      Instruction instruction;

      if (!operation.empty())
        instruction.setOperation(operation);

      if (!label.empty()) 
        instruction.setLabel(label);

      if (!parameters.empty()) {
        for (list<string>::iterator pit=parameters.begin(); pit != parameters.end(); pit++)
          instruction.addParameter(*pit);
      }
      instructions.push_back(instruction);

      comment = false;
    }
};

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
