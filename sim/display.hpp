#pragma once

#include <string>

#include "bus.hpp"

class StdDisplay : public Device {
public:
    uint8_t issueCommand(uint8_t data, uint32_t command) override;
private:
    std::string buffer = "";
};

