#ifndef IMMEDIATE_H
#define IMMEDIATE_H

#include <string>
using namespace std;

#include "global_objects.h"

class immediate {
public:
    // Checks if the operand is an immediate value (not a register or memory reference)
    bool isImmediate(string &operand);

    // Checks if the operand refers to memory (e.g., contains square brackets)
    bool isMemory(string &operand);

    // Returns the numeric value of an immediate operand (handles hex and decimal)
    int8_t getData(string &operand);

    // Determines if a string is a hexadecimal number (starts with 0x or 0X)
    bool checkIfHex(string &str);

    // Converts a hexadecimal string (0x-prefixed) into a decimal int8_t value
    int8_t convertHexToDecimal(string &hexString);

    // Converts a character to uppercase (if it's lowercase a-z)
    void toUpperCase(char &ch);
};

#endif // IMMEDIATE_H
