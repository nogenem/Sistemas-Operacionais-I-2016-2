/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU_Segmentation.cpp
 * Author: cancian
 * 
 * Created on 27 de Setembro de 2016, 20:08
 */

#include "HW_MMU_Segmentation.h"
#include "HW_Machine.h"

#include "Simulator.h"

HW_MMU_Segmentation::HW_MMU_Segmentation() {
}

HW_MMU_Segmentation::HW_MMU_Segmentation(const HW_MMU_Segmentation& orig) {
}

HW_MMU_Segmentation::~HW_MMU_Segmentation() {
}

HW_MMU_Segmentation::Register HW_MMU_Segmentation::readRegister(unsigned int registerNum) {
    if (registerNum == 0) {
        return this->_STBR;
    }
    return 0;
}

void HW_MMU_Segmentation::writeRegister(unsigned int registerNum, HW_MMU_Segmentation::Register value) {
    if (registerNum == 0) {
        this->_STBR = value;
    }
}

HW_MMU_Segmentation::PhysicalAddress HW_MMU_Segmentation::translateAddress(HW_MMU_Segmentation::LogicalAddress logical, HW_MMU_Segmentation::Operation operation) {
    unsigned int logicalSegmentNumber = (logical & HW_MMU_Segmentation::mask_LogicalSegment) >> HW_MMU_Segmentation::off_LogicalSegment;
    unsigned int logicalSegmentOffset = (logical & HW_MMU_Segmentation::mask_SegmentOffset) >> HW_MMU_Segmentation::off_SegmentOffset; 
    PhysicalAddress segmentEntryAddress = this->_STBR + logicalSegmentNumber;
    Information segmentEntry = HW_Machine::RAM()->read(segmentEntryAddress);

    unsigned int segmentSize = (segmentEntry & HW_MMU_Segmentation::mask_Limit) >> HW_MMU_Segmentation::off_Limit;    
    bool isSegmentInMemory = (segmentEntry & HW_MMU_Segmentation::mask_vality) > 0;
    bool hasProtectionError = (!(segmentEntry & HW_MMU_Segmentation::mask_read) && (operation==Operation::Read) );
    hasProtectionError |= (!(segmentEntry & HW_MMU_Segmentation::mask_write) && (operation==Operation::Write) );
    hasProtectionError |= (logicalSegmentOffset > segmentSize);
    
    if (hasProtectionError) {
        // schedule an event to notify that a protection error just happened
        Simulator* simulator = Simulator::getInstance();
        Entity* entity = simulator->getEntity();
        entity->getAttribute("MethodName")->setValue("MMU::protection_error_interrupt_handler()");
        simulator->insertEvent(simulator->getTnow(), HW_Machine::Module_HardwareEvent(), entity);
    } else if (isSegmentInMemory) {
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