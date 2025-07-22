CPU_Simulator is a simple CPU simulator written in C that emulates basic CPU behavior with virtual registers, memory, and instruction execution. It supports a set of custom assembly-like commands and maintains execution history for rollback functionality.

Features

• Virtual CPU components:

    •8 general-purpose registers (R0 - R7)

    •256 memory cells
    
    •Working Status Register (WSR)
    
    •Instruction Pointer (IP)

• Supported commands:

    START — initialize CPU, clear registers and memory
    
    ADD R<d>, R<s1>, R<s2> — add values from two registers and store in destination register
    
    ADD R<d>, R<s>, <value> — add immediate value to register
    
    SUB R<d>, R<s1>, R<s2> — subtract values from two registers
    
    SUB R<d>, R<s>, <value> — subtract immediate value from register
    
    MOV R<d>, R<s> — move value from one register to another
    
    MOV R<d>, <value> — assign immediate value to register
    
    LOAD R<d>, <address> — load value from memory into register
    
    STORE R<s>, <address> — store register value into memory address
    
    DISC <n> — rollback n steps from history
    
    DISC — rollback 1 step (default)
    
    LAYO — display current state of registers and memory
    
    EXIT — exit the simulator

• Execution history:

  History is saved to history.txt
  
  Allows rolling back previous states using DISC

• Simple and clean terminal interface

Compilation

To compile the simulator, use:

    gcc cpu_simulator.c -o cpu_simulator

Usage

To start the simulator, run:

    ./cpu_simulator
    
Example interaction:

plaintext

    > START
    CPU started. Memory and registers cleared.
    
    > MOV R0, 5
    
    > MOV R1, 10
    
    > ADD R2, R0, R1
    
    > STORE R2, 50
    
    > LAYO
    Registers:
    R0: 5 R1: 10 R2: 15 R3: 0 ... R7: 0
    
    Instruction Pointer: 5
    Working Status Register: 1
    Memory (non-zero values):
    Memory[50]: 15
    
    > DISC 2
    Rolled back 2 steps.
    
    > LAYO
    ...
    
    > EXIT
    Exiting CPU Simulator.
    
Notes

This project was created for educational purposes to practice C programming and understand low-level CPU concepts, including memory manipulation, register management, instruction parsing, and simple history management.

Author

Created by a student passionate about system programming and low-level development.
