#include "immediate.h"

// Check if the operand is an immediate value (not register and not memory)
bool immediate::isImmediate(string &operand) {
    return (!reg.isRegister(operand) && !isMemory(operand));
}

// Check if the operand refers to memory by looking for square brackets
bool immediate::isMemory(string &operand) {
    for (auto &ch : operand) {
        if (ch == '[')
            return true;
    }
    return false;
}

// Convert string operand to actual numeric value (supports decimal and hexadecimal)
int8_t immediate::getData(string &operand) {
    int8_t result = 0;

    if (checkIfHex(operand)) {
        result = convertHexToDecimal(operand);
    } else {
        result = int8_t(stoi(operand));  // assumes valid decimal string
    }

    return result;
}

// Check if the string is a hexadecimal number (starts with "0x" or "0X")
bool immediate::checkIfHex(string &str) {
    return (str.size() > 1 && (str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X"));
}

// Convert a hexadecimal string (e.g., "0x1F") to decimal value
int8_t immediate::convertHexToDecimal(string &hexString) {
    // Remove "0x" prefix
    hexString = hexString.substr(2);

    // Convert all characters to uppercase to simplify parsing
    for (auto &ch : hexString) {
        toUpperCase(ch);
    }

    int8_t decimalValue = 0;
    uint16_t multiplier = 1;

    // Convert each hex digit from right to left
    for (int i = hexString.size() - 1; i >= 0; --i) {
        char ch = hexString[i];
        if (ch >= 'A') {
            decimalValue += uint16_t(int(ch - 'A' + 10) * multiplier);
        } else {
            decimalValue += uint16_t(int(ch - '0') * multiplier);
        }
        multiplier *= 16;
    }

    return decimalValue;
}

// Convert character to uppercase (if it's a lowercase letter)
void immediate::toUpperCase(char &c) {
    if (c >= 'a' && c <= 'z')
        c -= 32;
}