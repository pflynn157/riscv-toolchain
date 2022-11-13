#include <cstdio>

#include "bus.hpp"

Bus::Bus() {
    devices = new Device*[256];
    for (int i = 0; i<256; i++) devices[i] = nullptr;
}

uint8_t Bus::issueCommand(uint8_t port, uint32_t command, uint8_t data) {
    if (devices[port] == nullptr) {
        return 0xFF;
    }
    
    Device *device = devices[port];
    if (device == nullptr) return 0;
    return device->issueCommand(data, command);
}

void Bus::attachDevice(uint8_t port, Device *device) {
    devices[port] = device;
}

