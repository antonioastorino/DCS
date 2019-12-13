//
//  DCSComponent.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSComponent::DCSComponent(std::string name, bool add):
enabled(true),		// only 3-state buffer can be disabled
name{name},
reachableIn(0),
connectedIn(0),
fromTristateIn(0),
isNode(false),
isTristate(false) {
	if (add) DCSEngine::addComponent(this);
}

DCSComponent::~DCSComponent() {
	for (auto wire: wireVector) {
		delete wire;
	}
}

// set single input
void DCSComponent::setIn(bool inVal, ushort inPinNum) {
	if (inPinNum >= getNumOfInPins()) throw "Input pin number out of range";
	reachableIn |= 1 << inPinNum;
	in &= (~(1 << inPinNum)); // reset inPinNum-th bit
	in |= (inVal << inPinNum); // set the same bit to inVal
}

// set entire input array
void DCSComponent::setIn(uint64_t inVec) {
	in = inVec;
	reachableIn = getAllReachedQWord();
}

// get single output
bool DCSComponent::getOutVal(ushort outPinNum) {
	if (reachableIn == getAllReachedQWord()) initialized = true;
	return (out >> outPinNum) & 1;
}


// get entire input array
uint64_t DCSComponent::getOutVec() {
	if (reachableIn == getAllReachedQWord()) initialized = true;
	return out;
}

void DCSComponent::connect(DCSComponent* to,
						   ushort outPinNum,
						   ushort inPinNum,
						   std::string probeName) {

	DCSComponent* leftComponent = getOutComponent(outPinNum);
	DCSComponent* rightComponent = to->getInComponent(inPinNum);
	
	if (leftComponent->isTristate) {
		rightComponent->setFromTristateIn(inPinNum);
	}
	else {
		rightComponent->setConnectedIn(inPinNum);
	}
	
	bool addToTheRight = true;
	for (auto component: leftComponent->rightComponentVector) {
		if (rightComponent == component) {
			addToTheRight = false;
			break;
		}
	}
	if (addToTheRight) leftComponent->rightComponentVector.push_back(rightComponent);
	
	
	DCSWire* wire = new DCSWire(leftComponent,
								outPinNum,
								rightComponent,
								inPinNum,
								probeName);
	
	wireVector.push_back(wire);
	DCSEngine::addWire(wire);
}

std::string DCSComponent::getName() { return name; }

DCSComponent* DCSComponent::getInComponent(ushort &inPinNum) {
	return this;
}

DCSComponent* DCSComponent::getOutComponent(ushort &outPinNum) {
	return this;
}

bool DCSComponent::getConnectedIn(ushort inPinNum) {
	return connectedIn & (1 << inPinNum);
}

bool DCSComponent::getFromTristateIn(ushort inPinNum) {
	return fromTristateIn & (1 << inPinNum);
}

void DCSComponent::setConnectedIn(ushort inPinNum) {
	if (getConnectedIn(inPinNum) || getFromTristateIn(inPinNum)) {
		DCSLog::error(name, "trying to connect output to connected input");
	}
	connectedIn |= (1 << inPinNum);
}

void DCSComponent::setFromTristateIn(ushort inPinNum) {
	if (getConnectedIn(inPinNum)) {
		DCSLog::error(name, "trying to connect tristate output to connected input");
	}
	fromTristateIn |= (1 << inPinNum);
}

void DCSComponent::propagateValues() {
	for (auto wire: wireVector) {
		wire->propagateValue();
	}
}

bool DCSComponent::isFullyConnected() {
	return (connectedIn ^ fromTristateIn) == getAllReachedQWord();
}

///* Setting the parent ensures that the parent's output is updated every
// time the child's output changes
// */
//void DCSComponent::setParent(DCSComponent* parent) {
//	this->parent = parent;
//}

//void DCSComponent::updateParentOut() {
//	if (parent != nullptr) parent->updateOut();
//}

uint64_t DCSComponent::getAllReachedQWord() { return (1 << getNumOfInPins()) - 1; }

void DCSComponent::enable(){
	throw "Only 3-state buffers can access this function";
}

void DCSComponent::disable(){
	throw "Only 3-state buffers can access this function";
}

bool DCSComponent::getEnabled(){
	return enabled;
}
