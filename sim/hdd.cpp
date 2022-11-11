#include <iostream>
#include <cstdio>

#include "hdd.hpp"

Hdd::Hdd(std::string path) {
    file = fopen(path.c_str(), "rwb+");
    if (file == NULL) {
        std::cerr << "Error: Invalid virtual disk file." << std::endl;
    }
}

//
// Commands:
// 0 -> IDENTIFY (returns 1 if found)
// 1 -> READ (rd holds the data)
// 2 -> WRITE (rd is the destination)
// 3 -> POS (rd holds the position)
//
uint8_t Hdd::issueCommand(uint8_t data, uint32_t command) {
    if (file == NULL) return 0;

    switch (command) {
        // IDENTIFY
        case 0: return 1;
        
        // READ
        case 1: {
            uint8_t data2;
            fread(&data2, sizeof(uint8_t), 1, file);
            return data2;
        }
        
        // WRITE
        case 2: {
            fwrite(&data, sizeof(uint8_t), 1, file);
            return 0;
        }
        
        // POSITION
        case 3: {
            position = data;
            fseek(file, position, SEEK_SET);
            return position;
        }
        
        default: {}
    }
    
    return 0;
}

void Hdd::close() {
    fclose(file);
}

