#ifndef __INSTRUCTION_H__
#define __INSTRUCTION_H__

#include "iasm.h"

class Instruction {
  private:
    string label;
    string operation;
    list<string> parameters;

  public:
    Instruction();
    Instruction(string operation);
    string toString();
    void addParameter(string val);
    string getOperation();
    void setOperation(string value);
    string getLabel();
    void setLabel(string value);

  private:
    void init(string operation);
};
#endif // __INSTRUCTION_H__
