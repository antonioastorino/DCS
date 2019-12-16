//
//  DCSAnd.hpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#ifndef DCSAnd_hpp
#define DCSAnd_hpp

class DCSAnd: public DCSComponent {
public:
	DCSAnd(std::string name);
	
	ushort getNumOfInPins() override { return 2; };
	ushort getNumOfOutPins() override { return 1; };
	
	void updateOut() override;
	int getTimeDelay() override { return 1; };
};

#endif /* DCSAnd_hpp */
