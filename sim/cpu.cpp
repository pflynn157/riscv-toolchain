#include <cstring>
#include <iostream>

#include "cpu.hpp"
#include "config.hpp"

//
// Initializies the CPU
//
CPU::CPU(RAM *ram, Bus *bus, uint32_t pc) {
    registers = new uint32_t[32];
    this->pc = pc;
    this->ram = ram;
    this->bus = bus;
}

//
// The main run loop
//
void CPU::run() {
    while (halt == false) {
        fetch();
        if (halt) break;
        decode();
        execute();
        store();
    }
}

//
// Fetch
//
void CPU::fetch() {
    reset();
    instr = ram->getMemory(pc);
    pc += 4;
    
    if (instr == 0xFFFFFFFF) halt = true;
}

//
// Decode
//
void CPU::decode() {
    // First, break down instructions into their component parts
    uint8_t opcode =  (uint8_t)(instr & 0b00000000000000000000000001111111);
             rd =     (uint8_t)((instr & 0b00000000000000000000111110000000) >> 7);
    uint32_t imm_u = (uint32_t)((instr & 0b11111111111111111111000000000000) >> 12);
    uint8_t func3 =  (uint8_t)((instr & 0b00000000000000000111000000000000) >> 12);
            rs1 =    (uint8_t)((instr & 0b00000000000011111000000000000000) >> 15);
    uint32_t imm_i = (uint32_t)((instr & 0b11111111111100000000000000000000) >> 20);
            rs2 =    (uint8_t)((instr & 0b00000001111100000000000000000000) >> 20);
    uint8_t func7 =  (uint8_t)((instr & 0b11111110000000000000000000000000) >> 25);
    
    // Branch Imm: imm[4:1][11][10:5][12]
    uint32_t imm_b = ((uint32_t)(instr & 0x80000000) >> 19)
        | ((instr & 0x80) << 4)
        | ((instr >> 20) & 0x7e0)
        | ((instr >> 7) & 0x1e);
    if ((imm_b & 0x0800) != 0) {
        imm_b |= 0xFFFFF000;
    }
    
    if ((imm_i & 0x0200) != 0) {
        imm_i |= 0xFFFFF000;
    }
        
    // Store Imm: imm[4:0] imm[11:5]
    uint32_t imm_s = rd | (func7 << 5);
    
    // J-Types
    uint32_t imm_j = ((uint32_t)(instr & 0x80000000) >> 11)
        | (instr & 0xff000)              // imm[19:12]
        | ((instr >> 9) & 0x800)         // imm[11]
        | ((instr >> 20) & 0x7fe);       // imm[10:1]
    
    // Now, set the signals
    switch (opcode) {
        //
        // R-Types
        //
        case 0b0110011: {
            this->aluop = func3;
            this->reg_write = 1;
            if (func7 == 32) this->alu_invert = 1;
        } break;
        
        //
        // I-Types
        //
        case 0b0010011: {
            this->aluop = func3;
            this->alu_src = 1;
            this->reg_write = 1;
            this->imm = imm_i;
        } break;
        
        //
        // JALR/ECALL (I-TYPE)
        //
        case 0b1100111: {
            if (func3 == 0b111) {
                this->io = 1;
                this->imm = imm_i;
            } else {
                this->branch = 1;
                this->alu_src = 1;
                this->reg_write = 1;
                this->rs1_src = 1;
                this->pc_write = 1;
                this->imm = imm_i;
            }
        } break;
        
        //
        // B-Types
        //
        case 0b1100011: {
            this->branch = 1;
            this->imm = imm_b;
            this->aluop = func3;
        } break;
        
        //
        // Loads
        //
        case 0b0000011: {
            this->mem_read = 1;
            this->mem2reg = 1;
            this->alu_src = 1;
            this->reg_write = 1;
            this->imm = imm_i;
            this->aluop = func3;
        } break;
        
        //
        // Stores
        // S-Type
        //
        case 0b0100011: {
            this->mem_write = 1;
            this->alu_src = 1;
            this->imm = imm_s;
            this->aluop = func3;
        } break;
        
        //
        // LUI
        // U-Type
        //
        case 0b0110111: {
            this->alu_src = 1;
            this->reg_write = 1;
            this->imm = imm_u;
            this->addui = 1;
        } break;
        
        //
        // AUIPC
        // U-Type
        //
        case 0b0010111: {
            this->alu_src = 1;
            this->reg_write = 1;
            this->rs1_src = 1;
            this->imm = imm_u;
        } break;
        
        //
        // JAL | J-Type
        //
        case 0b1101111: {
            this->branch = 1;
            this->alu_src = 1;
            this->reg_write = 1;
            this->rs1_src = 0;
            this->pc_write = 1;
            this->imm = imm_j;
        } break;
        
        default: {}
    }
}

//
// Execute
//
void CPU::execute() {
    if (io) {
        io_command = imm;
        io_port = getRegister(rs1);
        io_data = getRegister(rd);
        return;
    }

    // For add upper immediate
    // TODO: May need to clean up
    if (addui) {
        setRegister(rd, imm << 12);
        return;
    }
    
    // JAL & JALR
    // TODO: This needs cleanup
    if (branch && pc_write) {
        // JALR
        if (rs1_src) {
            uint32_t src1 = getRegister(rs1);
            uint32_t dest = src1 + imm;
            setRegister(rd, pc);
            pc = dest;
        
        // JAL
        } else {
            setRegister(rd, pc);
            pc = imm;
        }
        return;
    }
    
    // Get the ALU inputs
    uint32_t src1 = getRegister(rs1);
    uint32_t src2 = 0;
    
    if (alu_src == 0) {
        src2 = getRegister(rs2);
    } else {
        if (mem_write) {
            src2 = imm;
            size2 = aluop;
            aluop = 0;
        } else if (mem_read) {
            src2 = imm;
            size2 = aluop;
            aluop = 0;
        } else {
            src2 = imm;
        }
    }
    
    // Execute
    uint32_t result = 0;
    
    // Branch mux
    if (branch) {
        result = executeBRU(src1, src2);
        if (result == 1) {
            int32_t imm2 = (int32_t)imm;
            pc += imm2 - 4;
        }
        
    } else {
        result = executeALU(src1, src2);
        
        // mem_write mux
        if (mem_write) {
            mem_write2 = true;
            address2 = result;
            data2 = getRegister(rs2);
        } else {
        
            // mem2reg mux
            if (mem2reg) {
                mem_read2 = true;
                address2 = result;
            } else {
                setRegister(rd, result);
            }
        }
    }
}

//
// The ALU
//
uint32_t CPU::executeALU(uint32_t src1, uint32_t src2) {
    switch (aluop) {
        // Add and Sub
        case 0: {
            if (alu_invert) return src1 - src2;
            return src1 + src2;
        } break;
        
        // Shift left
        case 1: return src1 >> src2;
        
        // SLT
        case 2: {
            if ((int)src1 < (int)src2) return 1;
            return 0;
        } break;
        
        // SLTU (set less than unsigned)
        case 3: {
            if (src1 < src2) return 1;
            return 0;
        } break;
        
        // XOR
        case 4: return src1 ^ src2;
        
        // SRL/SRA (shift right logic/arithmetic)
        // Logic vs arithmetic determined by func7
        case 5: {
            // TODO: We need to make the difference, this may not be right
            return src1 << src2;
        } break;
        
        // OR
        case 6: return src1 | src2;
        
        // AND
        case 7: return src1 & src2;
    }
    
    return 0;
}

//
// The BLU
// Branch-control unit
//
uint32_t CPU::executeBRU(uint32_t src1, uint32_t src2) {
    switch (aluop) {
        // BEQ
        case 0: {
            if (src1 == src2) return 1;
            return 0;
        }
        
        // BNE
        case 1: {
            if (src1 != src2) return 1;
            return 0;
        }
        
        // BLT
        case 4: {
            if ((int)src1 < (int)src2) return 1;
            return 0;
        }
        
        // BGE
        case 5: {
            if ((int)src1 >= (int)src2) return 1;
            return 0;
        }
        
        // BLTU
        case 6: {
            if (src1 < src2) return 1;
            return 0;
        }
        
        // BGEU
        case 7: {
            if (src1 >= src2) return 1;
            return 0;
        }
    }
    
    return 0;
}

//
// Store (write-back)
//
void CPU::store() {
    // How IO works:
    // Query the bus for the IO device, print an error if no IO device (TODO: Want this?)
    // If found, send the command and data
    // Save any data to RD
    //
    if (io) {
        uint32_t result = bus->issueCommand(io_port, io_command, io_data);
        setRegister(rd, result);
    }

    if (mem_write2) {
        switch (size2) {
            case 0b000: ram->setMemory8(address2, data2); break;
            case 0b001: ram->setMemory8(address2, data2); break;
            case 0b010: ram->setMemory32(address2, data2); break;
            default: {}
        }
    }
    
    if (mem_read2) {
        //uint32_t data = ram->getMemory(address2);
        //setRegister(rd, data);
        uint32_t data = 0;
        
        switch (size2) {
            case 0b000: data = ram->getMemory8(address2); break;
            case 0b001: data = ram->getMemory8(address2); break;
            case 0b010: data = ram->getMemory(address2); break;
            default: {}
        }
        
        setRegister(rd, data);
    }
}

//
// Resets all the signals
//
void CPU::reset() {
    instr = 0;
    rd = 0;
    rs1 = 0;
    rs2 = 0;
    branch = 0;
    mem_read = 0;
    mem2reg = 0;
    aluop = 0;
    mem_write = 0;
    alu_src = 0;
    reg_write = 0;
    rs1_src = 0;
    pc_write = 0;
    alu_invert = 0;
    addui = 0;
    io = 0;
    imm = 0;
    mem_read2 = 0;
    mem_write2 = 0;
    address2 = 0;
    data2 = 0;
    size2 = 0;
    io_command = 0;
    io_port = 0;
    io_data = 0;
}

