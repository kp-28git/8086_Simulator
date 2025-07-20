# 8086 Simulator with Two-Pass Assembler

This project implements a **functional simulator for the Intel 8086 microprocessor** using modern C++ along with a **custom-built two-pass assembler**. It is designed to simulate execution of 8086 assembly instructions in a structured, modular way while offering deep insight into instruction execution, register and flag manipulation, and memory addressing.

---

## Core Features

- **Two-Pass Assembler Design**:
  - **Pass 1**: Parses labels and constructs a symbol table.
  - **Pass 2**: Generates resolved instructions and binary representations.
  
- **Instruction Simulation**:
  - Supports common 8086 instructions including:
    - Data transfer: `MOV`
    - Arithmetic: `ADD`, `SUB`, `ADC`, `SBB`
    - Multiplication/Division: `MUL`, `DIV`
    
- **Operand Classification**:
  - Differentiates between register, memory, and immediate operands.
  - Accurate parsing and resolution of both decimal and hexadecimal formats.

- **Register File Simulation**:
  - Implements 8086 general-purpose (`AX`, `BX`, etc.), segment (`CS`, `DS`, etc.), and special registers (`SP`, `BP`, etc.).
  - Handles both 8-bit (`AH`, `AL`, etc.) and 16-bit registers with correct data access.

- **Flag Register Handling**:
  - Zero, Carry, and Overflow flags are updated based on arithmetic results using proper bit-level manipulation.

- **Memory Model**:
  - Supports effective address calculation for memory operands.
  - Can read/write simulated memory locations with accurate address mapping.

- **Execution Engine**:
  - Executes parsed assembly line-by-line while updating system state (registers, memory, flags).
  - Supports debugging output for register states and flag values.

---

## Technical Highlights

- **Object-Oriented Architecture**:
  - Each core unit (registers, memory, operands, instructions, etc.) is encapsulated in a separate class.
  
- **Modular Design**:
  - Clean separation between instruction metadata, operand decoding, register logic, and memory logic.

- **Flag Manipulation Logic**:
  - Implements bitmask-based setting and clearing of individual 8086 flags based on result evaluation.

- **Hexadecimal Conversion Utility**:
  - Converts `0x` prefixed strings to decimal using character-wise parsing, avoiding use of libraries like `std::stoi` for full control and low-level accuracy.
