#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>      // For int8_t, uint16_t, etc.
#include <string>
#include <vector>
#include <iostream>

#include "registers.h"
#include "global_objects.h"

class Memory
{
private:
    int8_t* memoryLocation;      // Simulated memory block
    int32_t totalSize;           // Total size of memory

public:
    // Constructor: Initializes memory with predictable pattern
    Memory();

    // Checks if the operand is a memory reference (contains brackets)
    bool isMemory(std::string& operand);

    // Converts a memory reference string (e.g., [BX+10]) to offset
    uint16_t convertStringToMemoryLocation(std::string& memoryExpr);

    // Converts a hexadecimal string (e.g., "0x1A" or "1Ah") to decimal
    uint16_t convertHexStringToDecimal(std::string& hexString);

    // Converts lowercase character to uppercase (in-place)
    void toUpperCase(char& c);

    // Checks if a string is in hexadecimal format (prefix or suffix based)
    bool isHexString(std::string& str);

    // Calculates the effective address (physical address) from a memory reference
    uint32_t stringToEffectiveAddress(std::string& memoryAddress);

    // Returns 8-bit data from a memory location given in string form
    int8_t getData(std::string& memoryAddress);

    // Computes final 20-bit physical address from segment:offset
    uint32_t calculateEffectiveAddress(std::string& segmentRegister, uint16_t offset);

    // Writes a byte of data to memory at the specified address
    void setMemoryLocation(std::string& memoryAddress, uint8_t value);
};

#endif // MEMORY_H
