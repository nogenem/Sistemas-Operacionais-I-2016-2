/*
 * File:   System.cpp
 * Author: cancian
 *
 * Created on October 9, 2015, 9:04 PM
 */

#include "OperatingSystem.h"
#include "Application.h"
#include "HW_CPU.h"
#include "HW_Machine.h"

Application OperatingSystem::CreateDefaultApplication() {
    Application app;
    HW_MMU::Information instruction;
    instruction = (HW_CPU::addi<<HW_CPU::off_opcode) + (HW_CPU::a0<<HW_CPU::off_rd) + (HW_CPU::zero<<HW_CPU::off_rs) + (1<<HW_CPU::off_const);
    app.addCode( instruction );
    instruction = (HW_CPU::RType<<HW_CPU::off_opcode) + (HW_CPU::syscall<<HW_CPU::off_funct);
    app.addCode( instruction );
    instruction = (HW_CPU::addi<<HW_CPU::off_opcode) + (HW_CPU::a0<<HW_CPU::off_rd) + (HW_CPU::a0<<HW_CPU::off_rs) + (1<<HW_CPU::off_const);
    app.addCode( instruction );    
    instruction = (HW_CPU::j<<HW_CPU::off_opcode) + (1<<HW_CPU::off_addr);
    app.addCode( instruction );
    return app;
}

void OperatingSystem::SetBootApplication(Application app) {
    std::list<Application::Information> code = app.getCode();
    HW_CPU::Register address = HW_Machine::CPU()->readRegister(HW_CPU::pc);
    HW_MMU::Information info;
    for(std::list<HW_MMU::Information>::iterator it = code.begin(); it != code.end(); it++) {
        info = (*it);
        HW_Machine::RAM()->write(address, info);
        address++;
    }
}


void OperatingSystem::Init() {
    HW_Machine::Init();
    SetBootApplication(CreateDefaultApplication());
}

 HW_MMU::Information OperatingSystem::asmm(std::string mnemonic) {
     HW_MMU::Information bincode;
     /* @TODO 
      */
     if (mnemonic == "Process:exec()") {
         bincode = 0xFFFFFFFF; // - (HW_CPU::addi<<24) + 
     }
     bincode = (HW_CPU::addi<<26) + (HW_CPU::s0<<21) + (HW_CPU::s1<<16) + 1;
     return bincode;
 }