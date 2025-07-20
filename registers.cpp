#include "registers.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>

Registers::Registers()
{
    // Mapping register names to pointers
    regi["AX"] = &AX; regi["BX"] = &BX; regi["CX"] = &CX; regi["DX"] = &DX;
    regi["BP"] = &BP; regi["SP"] = &SP; regi["DI"] = &DI; regi["SI"] = &SI;
    regi["FLAG"] = &flag;

    regi["AL"] = &AL; regi["BL"] = &BL; regi["CL"] = &CL; regi["DL"] = &DL;
    regi["AH"] = &AH; regi["BH"] = &BH; regi["CH"] = &CH; regi["DH"] = &DH;

    regi["CS"] = &CS; regi["DS"] = &DS; regi["ES"] = &ES; regi["SS"] = &SS;

    // Initialize all registers with random values (for simulation)
    int temp = rand();
    for (auto& reg : regi)
    {
        *(reg.second) = temp++;
    }

    // Set 8-bit registers based on 16-bit values
    AH = (AX >> 8) & 0xFF;
    AL = AX & 0xFF;
    BH = (BX >> 8) & 0xFF;
    BL = BX & 0xFF;
    CH = (CX >> 8) & 0xFF;
    CL = CX & 0xFF;
    DH = (DX >> 8) & 0xFF;
    DL = DX & 0xFF;

    // Segment defaults
    flag = 0;
    CS = 0;
    DS = 16384;
    ES = 2 * DS;
    SS = 3 * DS;
}

bool Registers::isSegmentRegister(const string& name)
{
    return name == "CS" || name == "DS" || name == "ES" || name == "SS";
}

bool Registers::isRegister(const string& name)
{
    return regi.count(name) > 0;
}

int32_t Registers::getData(const string& name)
{
    if (!isRegister(name))
    {
        std::cerr << name << " is not a valid register.\n";
        return -1;
    }
    return *(regi[name]);
}

void Registers::setValue(const string& name, int32_t val)
{
    if (!isRegister(name))
    {
        std::cerr << name << " is not a valid register.\n";
        return;
    }

    *regi[name] = val;

    char lastChar = name.back();
    std::string base = name.substr(0, 1) + "X";

    if (lastChar == 'H') {
        *regi[base] &= 0x00FF;
        *regi[base] |= (val << 8);
    } else if (lastChar == 'L') {
        *regi[base] &= 0xFF00;
        *regi[base] |= (val & 0xFF);
    } else if (lastChar == 'X') {
        *regi[name.substr(0, 1) + "L"] = val & 0x00FF;
        *regi[name.substr(0, 1) + "H"] = (val >> 8) & 0x00FF;
    }
}

void Registers::printRegisterMap(std::ofstream& output)
{
    for (const auto& reg : regi)
    {
        if (reg.first != "flag")
            output << reg.first << " " << *(reg.second) << "\n";
    }

    output << "\nFlags:\n";
    output << "carry "    << getFlagData("carry")    << "\n";
    output << "zero "     << getFlagData("zero")     << "\n";
    output << "overflow " << getFlagData("overflow") << "\n";
}

void Registers::printHexValue(const string& name)
{
    int32_t value = getData(name);
    std::stringstream ss;
    ss << std::hex << std::uppercase << value;
    std::cout << ss.str() << '\n';
}

void Registers::updateFlag(const string& name, bool value)
{
    if (name == "carry") {
        if (value) flag |= (1 << 0);
        else flag &= ~(1 << 0);
    } else if (name == "overflow") {
        if (value) flag |= (1 << 11);
        else flag &= ~(1 << 11);
    } else if (name == "zero") {
        if (value) flag |= (1 << 6);
        else flag &= ~(1 << 6);
    }
}

bool Registers::getFlagData(const string& name)
{
    if (name == "carry") {
        return flag & (1 << 0);
    } else if (name == "overflow") {
        return flag & (1 << 11);
    } else if (name == "zero") {
        return flag & (1 << 6);
    }
    return false;
}
