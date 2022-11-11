#pragma once

#include <cstdint>

class Device {
public:
    virtual uint8_t issueCommand(uint8_t data, uint32_t command) {
        return 0;
    }
};

//
// The BUS
// Our bus can hold 256 devices
// Any device must inherit from the device class above
//
class Bus {
public:
    Bus();
    uint8_t issueCommand(uint8_t port, uint32_t command, uint8_t data);
    void attachDevice(uint8_t port, Device *device);
private:
    Device **devices;
};

