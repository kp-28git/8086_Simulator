#ifndef REGISTERS_H
#define REGISTERS_H

#include <bits/stdc++.h>
using namespace std;

class Registers
{
private:
int32_t AX, BX, CX, DX;
    int32_t CS, DS, SS, ES;
    int32_t SP, BP, SI, DI;
    int32_t AL, BL, CL, DL;
    int32_t AH, BH, CH, DH;
    int32_t flag;

    // Map register names to their memory locations
    map<string, int32_t *> regi;

public:
    Registers();

    // Check if a register is a segment register
    bool isSegmentRegister(const string& name);

    // Check if a given string is a valid register name
    bool isRegister(const string& name);

    // Get value from a register
    int32_t getData(const string& name);

    // Set value to a register, and update AX-like register if AL/AH is used and vice versa
    void setValue(const string& name, int32_t val);

    // Print values of all registers to a file
    void printRegisterMap(std::ofstream &);

    // Print hexadecimal value of a register
    void printHexValue(const string& name);

    // Update the status flags (carry, zero, overflow)
    void updateFlag(const string& name, bool value);

    // Get the value of a particular flag
    bool getFlagData(const string& name);
};

#endif
