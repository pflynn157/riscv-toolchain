#pragma once

#include <cstdint>

#include "ram.hpp"
#include "bus.hpp"

class CPU {
public:
    explicit CPU(RAM *ram, Bus *bus, uint32_t pc = 0);
    void run();
    
    // Debug functions
    void printRegisters();
private:
    // Variables and structures
    uint32_t *registers;
    uint32_t pc;
    RAM *ram;
    Bus *bus;
    bool halt = false;
    
    //
    // Functions
    //
    void fetch();
    void decode();
    void execute();
    void store();
    void reset();
    
    uint32_t executeALU(uint32_t src1, uint32_t src2);
    uint32_t executeBRU(uint32_t src1, uint32_t src2);
    
    void setRegister(int reg, uint32_t data) {
        if (reg == 0) return;
        registers[reg] = data;
    }
    
    uint32_t getRegister(int reg) {
        return registers[reg];
    }
    
    //
    // Control signals
    //
    uint32_t instr = 0;       // From the fetch stage
    
    // Used by the decode and the execute stage
    int rd = 0;
    int rs1 = 0;
    int rs2 = 0;
    int branch = 0;
    int mem_read = 0;
    int mem2reg = 0;
    int aluop = 0;
    int mem_write = 0;
    int alu_src = 0;
    int reg_write = 0;
    int rs1_src = 0;
    int pc_write = 0;
    int alu_invert = 0;
    int addui = 0;          // add upper immediate
    int io = 0;             // for IO operations
    uint32_t imm = 0;       // The final, decoded immediate
    
    // Used by the write-back stage
    int mem_read2 = 0;
    int mem_write2 = 0;
    uint32_t address2 = 0;
    uint32_t data2 = 0;
    int size2 = 0;
    
    // For IO operations
    // These are handled by the write-back stage
    uint32_t io_command = 0;
    uint32_t io_port = 0;
    uint32_t io_data = 0;
};

