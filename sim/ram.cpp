#include <cstdio>
#include <cstring>
#include <iostream>

#include "ram.hpp"

//
// Sets up the memory
//
RAM::RAM(int size) {
    memory = new uint8_t[size];
    memory_size = size;
}

//
// Loads a program to the memory and sets the program counter
//
void RAM::loadProgram(std::string path, int start) {
    FILE *file = fopen(path.c_str(), "rb");
    int index = start;
    
    while (!feof(file)) {
        uint8_t data = 0;
        fread(&data, sizeof(uint8_t), 1, file);
        memory[index] = data;
        ++index;
    }
    
    fclose(file);
}

//
// Sets the contents of a particular location in memory
//
void RAM::setMemory8(uint32_t address, uint8_t item) {
    memory[address] = item;
}

//
// Sets a 32-bit location in memory
//
void RAM::setMemory32(uint32_t address, uint32_t item) {
    memcpy(&memory[address], &item, sizeof(uint32_t));
}

//
// Returns an 8-bit location in memory
//
uint8_t RAM::getMemory8(uint32_t address) {
    return memory[address];
}

//
// Returns a 32-bit location in memory
//
uint32_t RAM::getMemory(uint32_t address) {
    uint32_t item = 0;
    memcpy(&item, &memory[address], sizeof(uint32_t));
    return item;
}

//
// Flushes our memory file back to the disk
//
void RAM::flushMemory(std::string path) {
    FILE *file = fopen(path.c_str(), "wb");
    
    for (int i = 0; i<memory_size; i++) {
        fwrite(&memory[i], sizeof(uint8_t), 1, file);
    }
    
    fclose(file);
}

