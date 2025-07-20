#include <bits/stdc++.h>

#include "registers.h"
#include "global_objects.h"

#include "memory.h"
#include "immediate.h"
#include "operation.h"
#include "alu.h"
#include "memory_global_object.h"

using namespace std;

// to correct the initialization of AL,AH,BL,BH and so on according to AX,BX and so on

// global object of memory
Operation op;
alu al;
// immediate im;
// memory mem;

int random_val = rand();
// function prototypes
vector<string> preprocessInstruction(string &);
void processInstruction(vector<string> &);
void processMovInstruction(vector<string> &);
void processAddInstruction(vector<string> &);
void processSubInstruction(vector<string> &);
void processAdcInstruction(vector<string> &);
void processSbbInstruction(vector<string> &);
void processMulInstruction(vector<string> &);
void processDivInstruction(vector<string> &);
bool checkJumpInstruction(string &);
bool processJumpInstruction(string &);
void processCmpInstruction(vector<string> &);

void split_instruction_into_operation_and_operand(string &, vector<string> &);
void upperCase(char &);

// compare

void processCmpInstruction(vector<string> &op)
{
    string op1 = op[1];
    string op2 = op[2];

    if (reg.isRegister(op1) && reg.isRegister(op2))
    {
        int x = reg.getData(op1);
        int y = reg.getData(op2);
        if (x - y < 0)
        {
            reg.updateFlag("carry", 1);
            reg.updateFlag("zero", 0);
            reg.updateFlag("overflow", 0);
        }
        else if (x - y > 0)
        {
            reg.updateFlag("carry", 0);
            reg.updateFlag("zero", 0);
            reg.updateFlag("overflow", 0);
        }
        else
        {
            reg.updateFlag("carry", 0);
            reg.updateFlag("zero", 1);
            reg.updateFlag("overflow", 0);
        }
    }
    else if (mem.isMemory(op1) && reg.isRegister(op2))
    {
        int x = mem.getData(op1);
        int y = reg.getData(op2);
        if (x - y < 0)
        {
            reg.updateFlag("carry", 1);
            reg.updateFlag("zero", 0);
            reg.updateFlag("overflow", 0);
        }
        else if (x - y > 0)
        {
            reg.updateFlag("carry", 0);
            reg.updateFlag("zero", 0);
            reg.updateFlag("overflow", 0);
        }
        else
        {
            reg.updateFlag("carry", 0);
            reg.updateFlag("zero", 1);
            reg.updateFlag("overflow", 0);
        }
    }
    else if (mem.isMemory(op1) && mem.isMemory(op2))
    {
        int x = mem.getData(op1);
        int y = mem.getData(op2);
        if (x - y < 0)
        {
            reg.updateFlag("carry", 1);
            reg.updateFlag("zero", 0);
            reg.updateFlag("overflow", 0);
        }
        else if (x - y > 0)
        {
            reg.updateFlag("carry", 0);
            reg.updateFlag("zero", 0);
            reg.updateFlag("overflow", 0);
        }
        else
        {
            reg.updateFlag("carry", 0);
            reg.updateFlag("zero", 1);
            reg.updateFlag("overflow", 0);
        }
    }
    else
    {
        int x = reg.getData(op1);
        int y = mem.getData(op2);
        if (x - y < 0)
        {
            reg.updateFlag("carry", 1);
            reg.updateFlag("zero", 0);
            reg.updateFlag("overflow", 0);
        }
        else if (x - y > 0)
        {
            reg.updateFlag("carry", 0);
            reg.updateFlag("zero", 0);
            reg.updateFlag("overflow", 0);
        }
        else
        {
            reg.updateFlag("carry", 0);
            reg.updateFlag("zero", 1);
            reg.updateFlag("overflow", 0);
        }
    }
}

// spliting  instruction into operation & operands
void split_instruction_into_operation_and_operand(string &line, vector<string> &ans)
{
    int n = line.size();
    string curr = "";
    for (int i = 0; i < n; i += 1)
    {
        if (line[i] == ';')
            break;
        else if (line[i] == ' ' || line[i] == ',')
        {
            if (curr.size())
                ans.push_back(curr);
            curr = "";
        }
        else
        {
            curr.push_back(line[i]);
        }
    }

    if (curr.size())
        ans.push_back(curr);

    return;
}

// processing mov instruction
void processMovInstruction(vector<string> &v)
{
    string operand1 = v[1];
    string operand2 = v[2];

    // memory <- memory (illegal)
    if (mem.isMemory(operand1) && mem.isMemory(operand2))
    {
        cout << "both opernads can not be memory location \n";
        return;
    }

    // imediate < -memory / register(illegal)
    else if (im.isImmediate(operand1))
    {
        cout << "the destination can not be imediate value";
    }
    else
    {
        // reg <- reg
        if (reg.isRegister(operand1) && reg.isRegister(operand2))
        {
            if (operand2[1] != operand1[1] && (operand1[1] == 'X' || operand2[1] == 'X'))
            {
                cout << "the registers in mov instruction should be of the same size --> error \n";
                return;
            }
            reg.setValue(operand1, reg.getData(operand2));
        }
        // memory_location / register <- imediate
        else if (im.isImmediate(operand2))
        {
            if (reg.isRegister(operand1))
                reg.setValue(operand1, im.getData(operand2));
            else
                mem.setMemoryLocation(operand1, im.getData(operand2));
        }
        else
        {
            // memory <- register
            if (mem.isMemory(operand1) && reg.isRegister(operand2))
            {
                mem.setMemoryLocation(operand1, reg.getData(operand2));
            }
            // register <- memory
            else if (reg.isRegister(operand1) && mem.isMemory(operand2))
            {
                reg.setValue(operand1, mem.getData(operand2));
            }

            // invalid
            else
            {
                cout << "illegal_instruction\n";
                return;
            }
        }
    }
}

// processing add instruction
void processAddInstruction(vector<string> &v)
{
    string operand1 = v[1];
    string operand2 = v[2];

    al.performAddition(v[1], v[2]);
}

// processing sub instruction
void processSubInstruction(vector<string> &v)
{
    string operand1 = v[1];
    string operand2 = v[2];

    al.performSubtraction(v[1], v[2]);
}

// processing sbb instruction
void processSbbInstruction(vector<string> &v)
{
    string operand1 = v[1];
    string operand2 = v[2];

    al.performSubtractionWithCarry(v[1], v[2]);
}

// processing adc instruction
void processAdcInstruction(vector<string> &v)
{
    string operand1 = v[1];
    string operand2 = v[2];

    al.performAdditionWithCarry(v[1], v[2]);
}

// processing mul instruction
void processMulInstruction(vector<string> &v)
{
    string operand1 = v[1];

    al.performMultiplication(v[1]);
}

// processing mul instruction
void processDivInstruction(vector<string> &v)
{
    string operand1 = v[1];

    al.performDivision(v[1]);
}

// checking for jump instruction
bool checkJumpInstruction(string &op)
{
    return (op == "JE" || op == "JNE" || op == "JZ" || op == "JNZ" || op == "JC" || op == "JNC");
}

// checking for validity of jump instruction
bool processJumpInstruction(string &op)
{
    if (op == "JZ" || op == "JE")
        return reg.getFlagData("zero");
    else if (op == "JC")
        return reg.getFlagData("carry");
    else if (op == "JNZ" || op == "JNE")
        return (reg.getFlagData("zero") == 0);
    else if (op == "JNC")
        return (reg.getFlagData("carry") == 0);
    else
        return false;
}

// preocessing instruction
void processInstruction(vector<string> &v)
{
    string opration = v[0];

    if (opration == "MOV")
    {
        processMovInstruction(v);
    }
    else if (opration == "ADD")
    {
        processAddInstruction(v);
    }
    else if (opration == "SUB")
    {
        processSubInstruction(v);
    }
    else if (opration == "MUL")
    {
        processMulInstruction(v);
    }
    else if (opration == "ADC")
    {
        processAdcInstruction(v);
    }
    else if (opration == "SBB")
    {
        processSbbInstruction(v);
    }
    else if (opration == "DIV")
    {
        processDivInstruction(v);
    }
    else if (opration == "CMP")
    {
        processCmpInstruction(v);
    }
}

// preprocessing instruction
vector<string> preprocessInstruction(string &instruction)
{
    for (auto &i : instruction)
    {
        upperCase(i);
    }

    vector<string> v;
    split_instruction_into_operation_and_operand(instruction, v);

    int n = v.size();

    if (n == 0)
        return v;

    string opration = v[0];

    // int no_of_operands = op.get_number_of_operands(opration);

    // for (auto &i : v)
    // {
    //     cout << i << " ";
    // }
    // cout << '\n';

    return v;

    // if (no_of_operands != (n - 1) || no_of_operands == -1)
    // {
    //     cout << "illegal instruction\n";
    //     return;
    // }
}

void upperCase(char &c)
{
    if (c >= 'a' && c <= 'z') // converts to uppercase by changing ascii
        c -= 32;
}

int main(void)
{
    fstream inputfile;
    inputfile.open("input.txt", ios::in);

    map<int, vector<string>> instructions;
    map<string, int> symbol_table;

    int i = 1;
    if (inputfile.is_open())
    {
        string str;

        while (getline(inputfile, str))
        {
            cout << str << " ";
            vector<string> v;
            v = preprocessInstruction(str);

            if (v.size() && v[0].size() && v[0][v[0].size() - 1] == ':')
            {
                symbol_table[v[0].substr(0, v[0].size() - 1)] = i;
                v.erase(v.begin());
                instructions[i] = v;
            }
            else if (v.size())
            {
                instructions[i] = v;
            }
            i += 1;
        }
    }
    ofstream output;
    output.open("output.txt");

    for (int i = 1; i <= instructions.size(); i += 1)
    {
        if (instructions[i].size() == 0)
            continue;
        if (checkJumpInstruction(instructions[i][0]))
        {
            if (processJumpInstruction(instructions[i][0]))
            {
                i = symbol_table[instructions[i][1]] - 1;
            }
        }
        else
        {
            processInstruction(instructions[i]);
        }
    }

    reg.printRegisterMap(output);

    output.close();

    ofstream symbol;
    symbol.open("symbol_table.txt");

    for (auto &i : symbol_table)
        symbol << i.first << " " << i.second << "\n";
}