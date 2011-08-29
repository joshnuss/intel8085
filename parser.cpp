#include "parser.h"

Parser::Parser() {
  text = "";
  label = "";
  operation = "";
  comment = false;
}

void Parser::parse(list<Token> tokens) {
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

string Parser::toString() {
  stringstream result;
  
  for (list<Instruction>::iterator it=instructions.begin(); it != instructions.end(); it++) {
    result << it->toString() << endl;
  }

  return result.str();
}

void Parser::parseLineStart() {
  label = "";
  text = "";
  operation = "";
  parameters.clear();
}

void Parser::parseSemicolon() {
  comment = true;
}

void Parser::parseComma() {
  if (!text.empty()) {
    parameters.push_back(text);
    text = "";
  }
}

void Parser::parseText() {
  text = token.getValue();
}

void Parser::parseWhitespace() {
  if (!text.empty()) {
    if (operation.empty()) 
      operation = text;
    else 
      parameters.push_back(text);

    text = "";
  }
}

void Parser::parseColon() {
  label = text;
  text = "";
}

void Parser::parseLineEnd() {
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
