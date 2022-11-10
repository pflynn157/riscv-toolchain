#include <iostream>
#include <string>
#include <cstdio>

#include "cpu.hpp"
#include "bus.hpp"
#include "hdd.hpp"
#include "display.hpp"

int main(int argc, char **argv) {
    // Create RAM and load a program to it
    RAM *ram = new RAM(5632);
    ram->loadProgram("./boot.bin");
    
    Bus *bus = new Bus;
    Hdd *hd0 = new Hdd("./sata0.bin");
    bus->attachDevice(2, hd0);
    
    Display *dsp = new Display;
    bus->attachDevice(0, dsp);

    // RUN the CPU
    CPU *cpu0 = new CPU(ram, bus);
    cpu0->run();
    
    // Debug
    cpu0->printRegisters();
    ram->flushMemory("./memory.bin");
    
    hd0->close();
    
    return 0;
}

