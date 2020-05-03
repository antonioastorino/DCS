#include "DCSEngine.hpp"
#include "DCSInput.hpp"
#include "DCSLog.hpp"
#include "DCSOutput.hpp"
#include "DCSRam16x8.hpp"
#include "DCSTriStateBuffer8Bits.hpp"
#include "DCSUpCounterWithLoadAndAsyncSR.hpp"

void firstProgramTest() {
    // Instruction set
    uint16_t LDA = 0b0000;
    uint16_t ADD = 0b0010;
    uint16_t OUT = 0b1110;

    // the instruction is the MSHB and the data is the LSHB
    uint16_t program[16][2] = {{LDA, 15}, // LDA 15
                               {ADD, 14}, // LDA 14
                               {OUT, 0},  // OUT
                               {0, 0},    // Empty
                               {0, 0},    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
                               {0, 0},    {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};

    DCSLog::printTestName("First program");
    uint16_t hcp = 10;
    DCSEngine::initialize(hcp);

    DCSRam16x8 *ram = new DCSRam16x8("r");
    DCSEngine::programMemory(ram, program);

    DCSComponentArray<DCSInput> inArray0("In", ram->getNumOfInPins());
    DCSComponentArray<DCSOutput> outArray0("Out", 5);

    DCSDisplayNBits dispAddr("ADDR", 4);
    DCSDisplayNBits dispData("DATA", 8);
    DCSDisplayNBits dispOut("OUT", 8);

    inArray0.connect(ram);
    inArray0.connect(&dispAddr, {13, 16}, {0, 3});
    inArray0.connect(&dispData, {5, 12}, {0, 7});
    inArray0.connect(&outArray0, {0, 4}, {0, 4}, {"OE", "CLK", "R", "S", "WR"});
    ram->connect(&dispOut);

    inArray0[0]->makeSignal(1); // Enable
    inArray0[1]->makeSignal(std::string("1111111001")); // CLK
    inArray0[2]->makeSignal(0);                         // Clear
    inArray0[3]->makeSignal(0);                         // Preset
    inArray0[4]->makeSignal(0);                         // Write
    inArray0[5]->makeSignal(std::string("0000011100"));
    inArray0[7]->makeSignal(std::string("0000011100"));
    inArray0[15]->makeSignal({2, 1, 1}, 0, true);
    // READ MEMORY
    DCSEngine::run(15 * hcp, false);
}
