#ifndef ALU_H
#define ALU_H

#include <string>
#include "memory_global_object.h"
using namespace std;

class alu {
public:
    // Decodes an operand (register, memory, or immediate) and returns its value
    int32_t decodeOperand(string &operand);

    // Performs addition between two operands
    void performAddition(string &operand1, string &operand2);

    // Performs addition with carry
    void performAdditionWithCarry(string &operand1, string &operand2);

    // Performs subtraction between two operands
    void performSubtraction(string &operand1, string &operand2);

    // Performs subtraction with borrow (carry flag considered)
    void performSubtractionWithCarry(string &operand1, string &operand2);

    // Performs multiplication with a single operand (AX * operand)
    void performMultiplication(string &operand);

    // Performs division (AX / operand), stores quotient in AL and remainder in AH
    void performDivision(string &operand);

    // Transfers a value into a destination (used in MOV-type operations)
    void transferData(string &destination, int32_t &value);

    // Updates flags after ALU operation (zero, overflow, carry)
    void updateFlag(string type, string &op1, string &op2, int32_t &val1, int32_t &val2, int32_t &result);
};

#endif // ALU_H
