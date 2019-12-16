//
//  DCSAnd.cpp
//  Digital circuit simulator
//
//  Created by Antonio Astorino on 15/11/2019.
//  Copyright © 2019 Antonio Astorino. All rights reserved.
//

#include "DCSHeader.h"

DCSAnd::DCSAnd(std::string name):
DCSComponent(name) {};

void DCSAnd::updateOut(){ out = (in & (in >> 1)) & 1; }
