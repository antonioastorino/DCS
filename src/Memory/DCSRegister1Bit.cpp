#include "DCSRegister1Bit.hpp"
#include "DCSLog.hpp"

DCSRegister1Bit::DCSRegister1Bit(std::string name)
    : DCSComponent(name, false),
      node0(name + "-Load"),
      not0(name + "-Data"),
      and0(name + "-And0"),
      and1(name + "-And1"),
      or0(name + "-Or0"),
      dffsr0(name + "DFFSR0") {
    node0.connect(&not0, 0, 0);
    node0.connect(&and1, 0, 0);
    not0.connect(&and0, 0, 1);
    dffsr0.connect(&and0, 0, 0);
    and0.connect(&or0, 0, 0);
    and1.connect(&or0, 0, 1);
    or0.connect(&dffsr0, 0, 0);

    timeDelay    = 6;
    numOfInPins  = 5;
    numOfOutPins = 1;
}

DCSComponent* DCSRegister1Bit::getOutComponent(uint16_t outPinNum) {
    if (outPinNum == 0)
        return dffsr0.getOutComponent(outPinNum);
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRegister1Bit::getInComponent(uint16_t& inPinNum) {
    switch (inPinNum) {
    case 0: // Data in
        inPinNum = 1;
        return &and1;
    case 1: // Clock
        return dffsr0.getInComponent(inPinNum);
    case 2: // Clear
        return dffsr0.getInComponent(inPinNum);
    case 3: // Preset
        return dffsr0.getInComponent(inPinNum);
    case 4: // Load
        inPinNum = 0;
        return &node0;
    default:
        DCSLog::error(this->name, 11);
        return nullptr;
    }
}
void DCSRegister1Bit::updateOut() { DCSLog::error(name, 0); }
