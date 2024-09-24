//Mariam chstuges hl@ chem verjacrel :)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MEMORY_SIZE 256
#define REGISTER_COUNT 8

int registers[REGISTER_COUNT];
int memory[MEMORY_SIZE];
int WSR = 0;
int IP = 0;



void ADD(int dest, int src1, int src2) {
    registers[dest] = registers[src1] + registers[src2];
    IP++;
}
void ADD_VAL(int dest, int src1, int value) {
    registers[dest] = registers[src1] + value;
    IP++;
}

void SUB(int dest, int src1, int src2) {
    registers[dest] = registers[src1] - registers[src2];
    IP++;
}
void SUB_VAL(int dest, int src1, int value) {
    registers[dest] = registers[src1] - value;
    IP++;
}

void MOV(int dest, int src1) {
    registers[dest] = registers[src1];
    IP++;
}
void MOV_VAL(int dest, int value) {
    registers[dest] = value;
    IP++;
}

void LOAD(int dest, int address) {
    if (address < 0 || address >= MEMORY_SIZE) {
        printf("Error: Memory address %d out of bounds.\n", address);
        return;
    }
    registers[dest] = memory[address];
    IP++;
    printf("Loaded value %d from Memory[%d] into R%d.\n",memory[address], address, dest);
}

void STORE(int src, int address) {
     if (address < 0 || address >= MEMORY_SIZE) {
        printf("Error: Memory address %d out of bounds.\n", address);
        return;
    }
    memory[address] = registers[src];
    IP++;
    printf("Store value %d from R%d into Memory address %d.\n", memory[address], src, address);
}

void START() {
    WSR = 1;
    memset(memory, 0, sizeof(memory));
    IP = 0;
    printf("CPU initialized and memory reset.\n");
}

void EXIT() {
    if (WSR == 1) {
        WSR = 0;
        memset(registers, 0, sizeof(registers));
        memset(memory, 0, sizeof(memory));
        printf("CPU initialized and memory reset.\n");
    } else {
        printf("Terminate process.\n");
        exit(0);
    }
}

void LAYO() {
   printf("Registers: \n");
    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("R%d: %d ", i, registers[i]);
    }
    
    printf("\n");
    printf("Working Status Register: %d\n", WSR);

    printf("Memory: \n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i] != 0) {
            printf("Size: %d, Memory[%d]: %d ", MEMORY_SIZE, i, memory[i]);
        }
    }
    printf("\nInstruction Pointer: %d\n", IP);
}

void execute(char *instruction) {
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

    while (1) {
        printf("> ");
        fgets(instruction, sizeof(instruction), stdin);
        instruction[strcspn(instruction, "\n")] = 0;
        execute(instruction);
    }

    return 0;
}
