#include "DCSRegister8Bits.hpp"
#include "DCSLog.hpp"
#include "DCSRegister1Bit.hpp"

DCSRegister8Bits::DCSRegister8Bits(std::string name)
    : DCSComponent(name, false),
      registerArray(name + "-reg1Arr0_", 8),
      nodeArray({
          name + "-Clock",
          name + "-Clear",
          name + "-Preset",
          name + "-Load"}, 4) {
    // connect control signals
    for (uint16_t i = 0; i < 8; i++) {
        nodeArray.connect(registerArray[i], 0, 1);
        nodeArray.connect(registerArray[i], 1, 2);
        nodeArray.connect(registerArray[i], 2, 3);
        nodeArray.connect(registerArray[i], 3, 4);
    }

    timeDelay    = registerArray[0]->getTimeDelay();
    numOfInPins  = 12;
    numOfOutPins = 8;
}

DCSComponent* DCSRegister8Bits::getOutComponent(uint16_t outPinNum) {
    if (outPinNum < 8) {
        return registerArray.getOutComponent(outPinNum);
    }
    DCSLog::error(this->name, 10);
    return nullptr;
}

DCSComponent* DCSRegister8Bits::getInComponent(uint16_t& inPinNum) {
    if (inPinNum < 8) { // Data 0 to 7
        uint16_t elementNumber = inPinNum;
        inPinNum = 0;
        return registerArray[elementNumber]->getInComponent(inPinNum);
    } else if (inPinNum < 12) { // control signals
        inPinNum -= 8;
        return nodeArray.getInComponent(inPinNum);
    }
    DCSLog::error(this->name, 11);
    return nullptr;
}

void DCSRegister8Bits::updateOut() { DCSLog::error(this->name, 0); }
