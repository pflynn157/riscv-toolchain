#pragma once

#include <string>
#include <cstdint>

class RAM {
public:
    RAM(int size);
    
    //
    // Memory controller functions
    //
    void loadProgram(std::string path, int start = 0);
    void setMemory8(uint32_t address, uint8_t item);
    void setMemory32(uint32_t address, uint32_t item);
    uint8_t getMemory8(uint32_t address);
    uint32_t getMemory(uint32_t address);
    void flushMemory(std::string path);
    
private:
    uint8_t *memory;
    int memory_size = 0;
};
