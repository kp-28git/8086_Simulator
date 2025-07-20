#include "alu.h"

Memory mem;
immediate im;

// Decode operand: supports register, memory, or immediate values
int32_t alu::decodeOperand(string &operand) {
    if (reg.isRegister(operand)) {
        return reg.getData(operand);
    } else if (mem.isMemory(operand)) {
        return mem.getData(operand);
    } else if (im.isImmediate(operand)) {
        return int32_t(im.getData(operand));
    }
    return 0; // default fallback
}

// Perform basic addition between operand1 and operand2
void alu::performAddition(string &operand1, string &operand2) {
    int32_t val2 = decodeOperand(operand2);
    int32_t val1 = decodeOperand(operand1);
    int32_t result = val1 + val2;

    if (reg.isRegister(operand1)) {
        reg.setValue(operand1, result);
    } else if (mem.isMemory(operand1)) {
        mem.setMemoryLocation(operand1, result);
    } else {
        cout << "Invalid operand in ALU instruction\n";
    }

    updateFlag("addition", operand1, operand2, val1, val2, result);
}

// Perform subtraction: operand1 = operand1 - operand2
void alu::performSubtraction(string &operand1, string &operand2) {
    int32_t val2 = decodeOperand(operand2);
    int32_t val1 = decodeOperand(operand1);
    int32_t result = val1 - val2;

    if (reg.isRegister(operand1)) {
        reg.setValue(operand1, result);
    } else if (mem.isMemory(operand1)) {
        mem.setMemoryLocation(operand1, result);
    } else {
        cout << "Invalid operand in ALU instruction\n";
    }

    updateFlag("subtraction", operand1, operand2, val1, val2, result);
}

// Perform subtraction with carry: operand1 = operand1 - operand2 - carry
void alu::performSubtractionWithCarry(string &operand1, string &operand2) {
    int32_t val2 = decodeOperand(operand2);
    int32_t val1 = decodeOperand(operand1);
    int32_t carry = reg.getFlagData("carry");
    int32_t result = val1 - val2 - carry;

    if (reg.isRegister(operand1)) {
        reg.setValue(operand1, result);
    } else if (mem.isMemory(operand1)) {
        mem.setMemoryLocation(operand1, result);
    } else {
        cout << "Invalid operand in ALU instruction\n";
    }

    updateFlag("subtraction", operand1, operand2, val1, val2, result);
}

// Perform addition with carry: operand1 = operand1 + operand2 + carry
void alu::performAdditionWithCarry(string &operand1, string &operand2) {
    int32_t val2 = decodeOperand(operand2);
    int32_t val1 = decodeOperand(operand1);
    int32_t carry = reg.getFlagData("carry");
    int32_t result = val1 + val2 + carry;

    if (reg.isRegister(operand1)) {
        reg.setValue(operand1, result);
    } else if (mem.isMemory(operand1)) {
        mem.setMemoryLocation(operand1, result);
    } else {
        cout << "Invalid operand in ALU instruction\n";
    }

    updateFlag("addition", operand1, operand2, val1, val2, result);
}

// Perform multiplication based on 8086 operand sizes and conventions
void alu::performMultiplication(string &operand1) {
    long long result = decodeOperand(operand1);

    if (reg.isRegister(operand1)) {
        if (operand1.back() == 'X') {
            string op2 = "AX";
            result = reg.getData(op2) * reg.getData(operand1);
            reg.setValue(operand1, result & 0x0000FFFF);
            reg.setValue("DX", (result >> 16) & 0xFFFF); // upper word
        } else {
            string op2 = "AL";
            result = reg.getData(op2) * reg.getData(operand1);
            reg.setValue("AX", result);
        }
    } else {
        cout << "Invalid operand for multiplication\n";
    }
}

// Perform integer division (AX ÷ operand)
void alu::performDivision(string &operand) {
    int32_t denominator = decodeOperand(operand);
    int32_t numerator = reg.getData("AX");

    int32_t quotient = numerator / denominator;
    int32_t remainder = numerator % denominator;

    reg.setValue("AL", quotient);
    reg.setValue("AH", remainder);
}

// Update flags based on result of operation
void alu::updateFlag(string type, string &op1, string &op2, int32_t &val1, int32_t &val2, int32_t &result) {
    // Zero flag
    reg.updateFlag("zero", result == 0 ? 1 : 0);

    // Determine operand size (8-bit or 16-bit)
    int32_t sizeOfResult = 8;
    if (reg.isRegister(op1) && op1.back() == 'X') {
        sizeOfResult = 16;
    }

    // Overflow flag for signed result out of range
    if (sizeOfResult == 16 && (result >= (1 << 15) || result < -(1 << 15))) {
        reg.updateFlag("overflow", 1);
    } else {
        reg.updateFlag("overflow", 0);
    }

    // Carry flag for unsigned overflow
    if (sizeOfResult == 8 && (result >= (1 << 8))) {
        reg.updateFlag("carry", 1);
    } else {
        reg.updateFlag("carry", 0);
    }
}
