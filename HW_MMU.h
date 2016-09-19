/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HW_MMU.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 11:55
 */

#ifndef HW_MMU_H
#define HW_MMU_H

class HW_MMU {
    friend class ProblemTester;
public:
    typedef unsigned int PhysicalAddress;
    typedef unsigned long LogicalAddress;
    typedef unsigned int Information; // 32 bits, just like MIPS/DLX (memory is 32 bits wide. PC=PC+1, instead)
public:
    HW_MMU();
    HW_MMU(const HW_MMU& orig);
    virtual ~HW_MMU();
public:
    Information read(LogicalAddress address);
    void write(LogicalAddress address, Information data);
protected:
    PhysicalAddress getPhysical() const;
    void setLogical(LogicalAddress _logical);

    PhysicalAddress translateAddress(LogicalAddress logical);
private:
    LogicalAddress _logical;
    PhysicalAddress _physical;
    
};

#endif /* HW_MMU_H */

