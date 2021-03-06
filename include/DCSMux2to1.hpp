#ifndef DCSMux2to1_hpp
#define DCSMux2to1_hpp
#include "DCSAnd.hpp"
#include "DCSNode.hpp"
#include "DCSNot.hpp"
#include "DCSOr.hpp"
#include "DCSUnitDelay.hpp"

/**
 * @class DCSMux2to1
 * 2 to 1 multiplexer
 * 
 * @pinout
 * In 0  - Data in 0
 * In 1  - Data in 1
 * In 2  - Selector
 *
 * Out 0 - Data out 0
 * @end_pinout
 */
class DCSMux2to1 : public DCSComponent {
private:
    DCSAnd and0;
    DCSAnd and1;
    DCSNot not0;
    DCSUnitDelay del0;
    DCSOr or0;
    DCSNode node0;

public:
    DCSMux2to1(std::string name);

    DCSComponent* getInComponent(uint16_t& inPinNum) override;
    DCSComponent* getOutComponent(uint16_t outPinNum) override;

    void updateOut() override;
};

#endif /* DCSMux2to1_hpp */
