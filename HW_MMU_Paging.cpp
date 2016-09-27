/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU_Paging.cpp
 * Author: cancian
 * 
 * Created on 23 de Setembro de 2016, 16:49
 */

#include "HW_MMU_Paging.h"
#include "HW_Machine.h"

#include "Simulator.h"

HW_MMU_Paging::HW_MMU_Paging() {
}

HW_MMU_Paging::HW_MMU_Paging(const HW_MMU_Paging& orig) {
}

HW_MMU_Paging::~HW_MMU_Paging() {
}

 HW_MMU::Register HW_MMU_Paging::readRegister(unsigned int registerNum) {
     if (registerNum==0) {
        return this->_PTBR;
     }
     return 0;
 }
 void HW_MMU_Paging::writeRegister(unsigned int registerNum, HW_MMU::Register value) {
    if (registerNum==0) {
        this->_PTBR = value;
    } 
 }

HW_MMU::PhysicalAddress HW_MMU_Paging::translateAddress(HW_MMU::LogicalAddress logical, Operation operation) {
    unsigned int logicalPageNumber = (logical & HW_MMU_Paging::mask_LogicalPage) >> HW_MMU_Paging::off_LogicalPage;
    PhysicalAddress pageEntryAddress = this->_PTBR + logicalPageNumber;
    Information pageEntry = HW_Machine::RAM()->read(pageEntryAddress);
            
    bool isPageInMemory = (pageEntry & HW_MMU_Paging::mask_vality) > 0;
    bool hasProtectionError = (!(pageEntry & HW_MMU_Paging::mask_read) && (operation==Operation::Read) );
    hasProtectionError |= (!(pageEntry & HW_MMU_Paging::mask_write) && (operation==Operation::Write) );
    
    if (hasProtectionError) {
        // schedule an event to notify that a protection error just happened
        Simulator* simulator = Simulator::getInstance();
        Entity* entity = simulator->getEntity();
        entity->getAttribute("MethodName")->setValue("MMU::protection_error_interrupt_handler()");
        simulator->insertEvent(simulator->getTnow(), HW_Machine::Module_HardwareEvent(), entity);
    } else if (isPageInMemory) {
        PhysicalAddress phys = 0;
        return phys;
    } else { // page fault
        // schedule an event to notify that a protection error just happened
        Simulator* simulator = Simulator::getInstance();
        Entity* entity = simulator->getEntity();
        entity->getAttribute("MethodName")->setValue("MMU::chunk_fault_interrupt_handler()");
        simulator->insertEvent(simulator->getTnow(), HW_Machine::Module_HardwareEvent(), entity);
    }
}