#include <iostream>
#include <string>
#include <cstdio>

#include "cpu.hpp"
#include "bus.hpp"
#include "hdd.hpp"

int main(int argc, char **argv) {
    // Create RAM and load a program to it
    RAM *ram = new RAM(4096);
    ram->loadProgram("./program.bin");
    
    Bus *bus = new Bus;
    Hdd *hd0 = new Hdd("./sata0.bin");
    bus->attachDevice(2, hd0);

    // RUN the CPU
    CPU *cpu0 = new CPU(ram, bus);
    cpu0->run();
    
    // Debug
    cpu0->printRegisters();
    ram->flushMemory("./memory.bin");
    
    hd0->close();
    
    return 0;
}

