//
//  DCSTriStateBuffer.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 12/12/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSTriStateBuffer.hpp"

DCSTriStateBuffer::DCSTriStateBuffer(std::string name) :
DCSComponent(name, 2, 1) {
	isTristate = true;
	enabled = false; // disabled by default
}

void DCSTriStateBuffer::updateOut() {
	if ((in >> 1) & 1) {
		enable();
		
		out = in & 1;
		updateParentOut();
	}
	else { disable(); }
}

void DCSTriStateBuffer::enable(){ enabled = true;}
void DCSTriStateBuffer::disable(){ enabled = false;}
