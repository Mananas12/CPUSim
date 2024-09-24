#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MEMORY_SIZE 256 // size of memory
#define REGISTER_COUNT 8 // number of registers
#define INSTRUCTION_SIZE 20 // number of instructions
#define HISTORY_SIZE 20 // number of history

FILE * history_file; // location of history file

struct CPU_INFO{ // CPU information
    int registers[REGISTER_COUNT];
    int memory[MEMORY_SIZE];
    int WSR;
    int IP;
}typedef CPU_INFO;

CPU_INFO CPU;

void add_history(){ // add CPU information
    fwrite(&CPU, 1, sizeof(CPU_INFO), history_file);
}

void ADD(int dest, int src1, int src2) { // addition point
    CPU.registers[dest] = CPU.registers[src1] + CPU.registers[src2];
    CPU.IP++;
    add_history();
}
void ADD_VAL(int dest, int src1, int value) { // addition point with value
    CPU.registers[dest] = CPU.registers[src1] + value;
    CPU.IP++;
    add_history();
}

void SUB(int dest, int src1, int src2) { // subtraction point
    CPU.registers[dest] = CPU.registers[src1] - CPU.registers[src2];
    CPU.IP++;
    add_history();
}
void SUB_VAL(int dest, int src1, int value) { // subtraction point with value
    CPU.registers[dest] = CPU.registers[src1] - value;
    CPU.IP++;
    add_history();
}

void MOV(int dest, int src1) { // move point
    printf("MOV");
    CPU.registers[dest] = CPU.registers[src1];
    CPU.IP++;
    add_history();
}
void MOV_VAL(int dest, int value) { // move with value
    CPU.registers[dest] = value;
    CPU.IP++;
    add_history();
}

void LOAD(int dest, int address) { // load point
    if (address < 0 || address >= MEMORY_SIZE) {
        printf("Error: Memory address %d out of bounds.\n", address);
        return;
    }
    CPU.registers[dest] = CPU.memory[address];
    CPU.IP++;
    printf("Loaded value %d from Memory[%d] into R%d.\n",CPU.memory[address], address, dest);
}

void STORE(int src, int address) { // store point
     if (address < 0 || address >= MEMORY_SIZE) {
        printf("Error: Memory address %d out of bounds.\n", address);
        return;
    }
    CPU.memory[address] = CPU.registers[src];
    CPU.IP++;
    printf("Store value %d from R%d into Memory address %d.\n", CPU.memory[address], src, address);
}

void START() { // start point

    CPU.WSR = 1;
    memset(CPU.memory, 0, sizeof(CPU.memory));
    CPU.IP = 0;
    printf("CPU initialized and memory reset after start.\n");
}

void EXIT() { // exit point
    if (CPU.WSR == 1) {
        CPU.WSR = 0;
        memset(CPU.registers, 0, sizeof(CPU.registers));
        memset(CPU.memory, 0, sizeof(CPU.memory));
        printf("CPU initialized and memory reset after exit.\n");
    } else {
        printf("Terminate process.\n");
        exit(0);
    }
}

void DISC(int num) { // previous instruction point
    if(num  < CPU.IP){
        printf("num < IP\n");
        return;
    }
    fseek(history_file, SEEK_SET,(CPU.IP - num - 1) * sizeof(CPU));
    fread(&CPU, 1, sizeof(CPU_INFO), history_file);
    ftruncate(fileno(history_file), sizeof(CPU_INFO) * CPU.IP);
}

void LAYO() { // display point
   printf("Registers: \n");
    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("R%d: %d ", i, CPU.registers[i]);
    }
    
    printf("\n");
    printf("Working Status Register: %d\n", CPU.WSR);

    printf("Memory: \n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (CPU.memory[i] != 0) {
            printf("Size: %d, Memory[%d]: %d ", MEMORY_SIZE, i, CPU.memory[i]);
        }
    }
    printf("\nInstruction Pointer: %d\n", CPU.IP);
}

void execute(char *instruction) { // execute instruction
    char operation[10];
    int dest, src, src1, src2, address, value, n;
    
    if (sscanf(instruction, "ADD R%d, R%d, R%d", &dest, &src1, &src2) == 3) {
        ADD(dest, src1, src2);
    } else if (sscanf(instruction, "ADD R%d, R%d, %d", &dest, &src1, &value) == 3) {
        ADD_VAL(dest, src1, value);
    } else if (sscanf(instruction, "SUB R%d, R%d, R%d", &dest, &src1, &src2) == 3) {
        SUB(dest, src1, src2);
    } else if (sscanf(instruction, "SUB R%d, R%d, %d", &dest, &src1, &value) == 3) {
        SUB_VAL(dest, src1, value);
    } else if (sscanf(instruction, "MOV R%d, R%d", &dest, &src1) == 2) {
        MOV(dest, src1);
    } else if (sscanf(instruction, "MOV R%d, %d", &dest, &value) == 2) {
        MOV_VAL(dest, value);
    } else if (sscanf(instruction, "LOAD R%d, %d", &dest, &address) == 2) {
        LOAD(dest, address);
    } else if (sscanf(instruction, "STORE R%d, %d", &src, &address) == 2) {
        STORE(src, address);
    } else if (strcmp(instruction, "START") == 0) {
        START();
    } else if (strcmp(instruction, "EXIT") == 0) {
        EXIT();
    } else if (sscanf(instruction, "DISC %d", &n) == 1) {
        DISC(n);
    } else if (sscanf(instruction, "DISC") == 0) {
        DISC(1);
    } else if (strcmp(instruction, "LAYO") == 0) {
        LAYO();
    } else if (sscanf(instruction, "add R%d, R%d, R%d", &dest, &src1, &src2) == 3) {
        ADD(dest, src1, src2);
    } else if (sscanf(instruction, "add R%d, R%d, %d", &dest, &src1, &value) == 3) {
        ADD_VAL(dest, src1, value);
    } else if (sscanf(instruction, "sub R%d, R%d, R%d", &dest, &src1, &src2) == 3) {
        SUB(dest, src1, src2);
    } else if (sscanf(instruction, "sub R%d, R%d, %d", &dest, &src1, &value) == 3) {
        SUB_VAL(dest, src1, value);
    } else if (sscanf(instruction, "mov R%d, R%d", &dest, &src1) == 2) {
        printf("mov exception\n");
        MOV(dest, src1);
    } else if (sscanf(instruction, "mov R%d, %d", &dest, &value) == 2) {
        MOV_VAL(dest, value);
    } else if (sscanf(instruction, "load R%d, %d", &dest, &address) == 2) {
        LOAD(dest, address);
    } else if (sscanf(instruction, "store R%d, %d", &src, &address) == 2) {
        STORE(src, address);
    } else if (strcmp(instruction, "start") == 0) {
        START();
    } else if (strcmp(instruction, "exit") == 0) {
        EXIT();
    } else if (sscanf(instruction, "disc %d", &n) == 1) {
        DISC(n);
    } else if (strcmp(instruction, "layo") == 0) {
        LAYO();
    } else {
        printf("Unknown instruction: %s\n", instruction);
    }
}

int main() {
    char instruction[50];

    printf("Simple CPU Simulator\n");
    printf("Enter assembly instructions:\n");
    history_file =  fopen("history.txt", "w+");

    if(history_file == NULL){
        perror("Open failed: \n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("> ");
        fgets(instruction, sizeof(instruction), stdin);
        instruction[strcspn(instruction, "\n")] = 0;
        execute(instruction);
    }

    return 0;
}
