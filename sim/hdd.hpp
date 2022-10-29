#pragma once

#include <string>
#include <cstdint>
#include <cstdio>

#include "bus.hpp"

class Hdd : public Device {
public:
    explicit Hdd(std::string path);
    uint32_t issueCommand(uint8_t data, uint32_t command) override;
    void close();
private:
    FILE *file;
    uint32_t position = 0;
};

