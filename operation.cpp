#include "operation.h"
#include <iostream>

Operation::Operation()
{
    // Define number of operands for supported instructions
    numberOfOperands["MOV"] = 2;
    numberOfOperands["ADD"] = 2;
    numberOfOperands["ADC"] = 2;
    numberOfOperands["SUB"] = 2;
    numberOfOperands["MUL"] = 1;
    numberOfOperands["DIV"] = 2;
    numberOfOperands["SBB"] = 2;
}

int Operation::getNumberOfOperands(std::string& op)
{
    if (numberOfOperands.count(op))
    {
        return numberOfOperands[op];
    }
    else
    {
        std::cerr << "[Error] Unsupported operation: \"" << op << "\"\n";
        return -1;
    }
}
