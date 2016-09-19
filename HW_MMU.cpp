/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 11:55
 */

#include "HW_MMU.h"
#include "HW_Machine.h"

HW_MMU::HW_MMU() {
    // INSERT YOUR CODE HERE
    // ...
    
}

HW_MMU::HW_MMU(const HW_MMU& orig) {
}

HW_MMU::~HW_MMU() {
}

HW_MMU::PhysicalAddress HW_MMU::translateAddress(LogicalAddress logical){
    PhysicalAddress physical;
    // Translate logical into physical address
    // INSERT YOUR CODE HERE
    // ...
    physical = logical; // immediate address translation  
    
    return physical;
}

HW_MMU::PhysicalAddress HW_MMU::getPhysical() const {
    return _physical;
}

void HW_MMU::setLogical(LogicalAddress _logical) {
    this->_logical = _logical;
    _physical = translateAddress(_logical); 
}


HW_MMU::Information HW_MMU::read(HW_MMU::LogicalAddress address) {
    PhysicalAddress phys = translateAddress(address);
    return HW_Machine::RAM()->read(phys);
}

void HW_MMU::write(HW_MMU::LogicalAddress address, HW_MMU::Information data) {
    PhysicalAddress phys = translateAddress(address);
    HW_Machine::RAM()->write(phys, data);
}
