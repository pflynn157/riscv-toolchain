#include <cstdio>

#include "bus.hpp"

Bus::Bus() {
    devices = new Device*[256];
}

uint32_t Bus::issueCommand(uint8_t port, uint32_t command, uint8_t data) {
    if (devices[port] == nullptr) {
        return 0xFFFFFFFF;
    }
    
    Device *device = devices[port];
    return device->issueCommand(data, command);
}

void Bus::attachDevice(uint8_t port, Device *device) {
    devices[port] = device;
}
