#include "memory.h"

Registers reg;

// Constructor to initialize memory with predictable data pattern
Memory::Memory()
{
    totalSize = 1048575;
    memoryLocation = new (nothrow) int8_t[totalSize];

    srand(unsigned(time(NULL)));
    uint8_t value = 1;

    for (int i = 0; i < totalSize; i++)
    {
        memoryLocation[i] = (value % 256);
        value = (value >= 255) ? 0 : value + 1;
    }
}

// Checks if the given operand is a memory operand
bool Memory::isMemory(string &operand)
{
    for (auto &ch : operand)
    {
        if (ch == '[')
            return true;
    }
    return false;
}

// Converts a string-based Memory operand into its offset
uint16_t Memory::convertStringToMemoryLocation(string &memLoc)
{
    uint16_t location = 0;
    string curr = "";
    vector<string> elements;

    for (auto &ch : memLoc)
    {
        if (ch == ':')
        {
            curr = "";
            continue;
        }
        if (ch == '[' || ch == ' ' || ch == ']' || ch == '+' || ch == '-')
        {
            if (!curr.empty())
                elements.push_back(curr);
            curr = (ch == '-') ? "-" : "";
        }
        else
        {
            curr.push_back(ch);
        }
    }
    if (!curr.empty())
        elements.push_back(curr);

    for (auto &token : elements)
    {
        if (reg.isRegister(token))
        {
            location += reg.getData(token);
        }
        else if (isHexString(token))
        {
            location += convertHexStringToDecimal(token);
        }
        else
        {
            location += stoi(token);
        }
    }
    return location;
}

// Converts character to uppercase
void Memory::toUpperCase(char &ch)
{
    if (ch >= 'a' && ch <= 'z')
        ch = char(ch - 32);
}

// Converts hexadecimal string to decimal (supports 0x.. or ..h format)
uint16_t Memory::convertHexStringToDecimal(string &hexStr)
{
    for (auto &ch : hexStr)
        toUpperCase(ch);

    if (hexStr.size() > 1 && hexStr.substr(0, 2) == "0X")
        hexStr = hexStr.substr(2);
    else
        hexStr = hexStr.substr(0, hexStr.size() - 1);

    uint16_t decimal = 0;
    uint16_t multiplier = 1;

    for (int i = hexStr.size() - 1; i >= 0; --i)
    {
        if (hexStr[i] >= 'A')
            decimal += uint16_t((hexStr[i] - 'A' + 10) * multiplier);
        else
            decimal += uint16_t((hexStr[i] - '0') * multiplier);

        multiplier *= 16;
    }
    return decimal;
}

// Checks if a string is a hexadecimal representation
bool Memory::isHexString(string &str)
{
    return str.size() > 1 && 
          ((str.substr(0, 2) == "0x" || str.substr(0, 2) == "0X") ||
           (str.back() == 'h' || str.back() == 'H'));
}

// Calculates effective address using segment and offset
uint32_t Memory::stringToEffectiveAddress(string &memoryAddress)
{
    uint16_t offset = convertStringToMemoryLocation(memoryAddress);
    string segment = "DS";

    for (int i = 0; i < memoryAddress.size() - 1; i++)
    {
        string token = memoryAddress.substr(i, 2);
        if (reg.isSegmentRegister(token))
        {
            segment = token;
        }
    }

    return calculateEffectiveAddress(segment, offset);
}

// Retrieves data from a given memory address
int8_t Memory::getData(string &memoryAddress)
{
    uint32_t address = stringToEffectiveAddress(memoryAddress);
    if (address < totalSize)
    {
        return memoryLocation[address];
    }
    else
    {
        cout << "Memory address out of range. Max: " << totalSize << '\n';
        return 0;
    }
}

// Computes linear address using segment and offset
uint32_t Memory::calculateEffectiveAddress(string &segmentRegister, uint16_t offset)
{
    return (reg.getData(segmentRegister) * 0x10) + offset;
}

// Sets a byte of memory at the given address
void Memory::setMemoryLocation(string &memoryAddress, uint8_t value)
{
    uint32_t address = stringToEffectiveAddress(memoryAddress);

    if (address < totalSize)
    {
        memoryLocation[address] = value;
    }
    else
    {
        cout << "Memory address out of range. Max: " << totalSize << '\n';
    }
}
