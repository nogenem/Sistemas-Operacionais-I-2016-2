/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU_Segmentation.h
 * Author: cancian
 *
 * Created on 27 de Setembro de 2016, 20:08
 */

#ifndef HW_MMU_SEGMENTATION_H
#define HW_MMU_SEGMENTATION_H

#include "HW_MMU.h"

class HW_MMU_Segmentation : public HW_MMU {
public:

    enum ILogAddr {
        off_LogicalSegment = 16, 
        off_SegmentOffset = 0,
        mask_LogicalSegment = 0xFFFF0000,
        mask_SegmentOffset  = 0x0000FFFF   // segment size limited to 16 bits so a segment entry fits one "Information"
    };

    enum SegmentEntry {
        mask_vality = 0x80000000,
        mask_read   = 0x40000000,
        mask_write  = 0x20000000,
        mask_exec   = 0x10000000,
        mask_M      = 0x08000000,
        mask_R      = 0x04000000,
        mask_Base   = 0x03FF0000,
        mask_Limit  = 0x0000FFFF,
        off_Base = 16,
        off_Limit = 0
    };
public:
    HW_MMU_Segmentation();
    HW_MMU_Segmentation(const HW_MMU_Segmentation& orig);
    virtual ~HW_MMU_Segmentation();
public:
    virtual Register readRegister(unsigned int registerNum);
    virtual void writeRegister(unsigned int registerNum, Register value);
protected:
    virtual PhysicalAddress translateAddress(LogicalAddress logical, Operation operation);
private:
    PhysicalAddress _STBR;

};

#endif /* HW_MMU_SEGMENTATION_H */

