#include <iostream>
#include <string>
#include <cstdio>

#include "cpu.hpp"

int main(int argc, char **argv) {
    // Create RAM and load a program to it
    RAM *ram = new RAM(4096);
    ram->loadProgram("./program.bin");

    // RUN the CPU
    CPU *cpu0 = new CPU(ram);
    cpu0->run();
    
    // Debug
    cpu0->printRegisters();
    ram->flushMemory("./memory.bin");
    
    return 0;
}

