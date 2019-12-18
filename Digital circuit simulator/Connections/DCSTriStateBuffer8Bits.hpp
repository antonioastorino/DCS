//
//  DCSTriStateBuffer8Bits.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 18/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSTriStateBuffer8Bits_hpp
#define DCSTriStateBuffer8Bits_hpp

class DCSTriStateBuffer8Bits: public DCSComponent {
private:
	DCSComponentArray<DCSTriStateBuffer> bufferArray;
	DCSNode node0;
public:
	DCSTriStateBuffer8Bits(std::string name);
	
	DCSComponent* getOutComponent(ushort &outPinNum) override;
	DCSComponent* getInComponent(ushort &inPinNum) override;
	void updateOut() override;
	
	ushort getNumOfInPins() override { return 9; };
	ushort getNumOfOutPins() override { return 8; };
	
	int getTimeDelay() override { return 1; };
	
	void enable() override;
	void disable() override;
};

#endif /* DCSTriStateBuffer8Bits_hpp */
