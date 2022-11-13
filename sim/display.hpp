#pragma once

#include <string>

#include "bus.hpp"
#include "run.hpp"

class CpuController;

class StdDisplay : public Device {
public:
    StdDisplay(CpuController *ctrl) { this->ctrl = ctrl; }
    uint8_t issueCommand(uint8_t data, uint32_t command) override;
private:
    std::string buffer = "";
    CpuController *ctrl;
};

