#include <iostream>

#include "cpu.hpp"

void CPU::printRegisters() {
    std::cout << "===============================" << std::endl;
    for (int i = 0; i<32; i++) {
        std::cout << "x" << i << ": " << registers[i] << " ";
        printf("\t\t\t(0x%x)", registers[i]);
        std::cout << std::endl;
    }
    std::cout << "===============================" << std::endl;
}

