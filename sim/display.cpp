#include <iostream>

#include "display.hpp"

//
// The commands for the display controller
// 1 -> Display
// 2 -> Clear
// 3 -> Load character
//
uint8_t StdDisplay::issueCommand(uint8_t data, uint32_t command) {
    switch (command) {
        // Display
        case 1: {
            emit ctrl->resultReady(QString::fromStdString(buffer));
        } break;
        
        // Clear
        case 2: {
            buffer = "";
        } break;
        
        // Load character
        case 3: {
            buffer += (char)data;
            return data;
        } break;
        
        default: {}
    }

    return 0;
}

