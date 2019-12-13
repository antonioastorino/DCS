//
//  DCSInput.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 22/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSInput.hpp"
#include "DCSEngine.hpp"

DCSInput::DCSInput(std::string name) :
DCSComponent(name, false),
signal({0}),
constValue(0){
	DCSEngine::addInput(this);
}

DCSInput::DCSInput(std::string name, bool constValue) :
DCSComponent(name, false),
signal({0}),
constValue(constValue){
	DCSEngine::addInput(this);
}

DCSInput::DCSInput(std::string name, binary_signal signal) :
DCSComponent(name, false),
signal(signal),
constValue(0) {
	hasSignal = true;
	DCSEngine::addInput(this);
}

void DCSInput::makeSignal(bool constValue) {
	this->constValue = constValue;
};
void DCSInput::makeSignal(binary_signal signal) {
	this->signal = signal;
	hasSignal = true;
}

void DCSInput::updateOut() {
	if (hasSignal) out = signal.getVal(DCSEngine::getStepNumber());
	else out = constValue;
}
