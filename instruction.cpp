#include "instruction.h"

Instruction::Instruction() {
  init("");
}

Instruction::Instruction(string operation) {
  init(operation);
}

string Instruction::toString() {
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

void Instruction::addParameter(string val) {
  parameters.push_back(val);
}

string Instruction::getOperation() {
  return operation;
}

void Instruction::setOperation(string value) {
  operation = value;
}

string Instruction::getLabel() {
  return label;
}

void Instruction::setLabel(string value) {
  label = value;
}

void Instruction::init(string operation) {
  this->operation = operation;
  label = "";
}
