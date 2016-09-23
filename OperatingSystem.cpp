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


void OperatingSystem::LoadApplication(Application* app, MMU::PhysicalAddress address) {
    std::list<Application::Information> code = app->getCode();
    HW_MMU::Information info;
    for(std::list<HW_MMU::Information>::iterator it = code.begin(); it != code.end(); it++) {
        info = (*it);
        HW_Machine::RAM()->write(address, info);
        address++;
    }    
}

void OperatingSystem::SetBootApplication(Application* app) {
    HW_CPU::Register address = HW_Machine::CPU()->readRegister(HW_CPU::pc);
    LoadApplication(app, address);
}


void OperatingSystem::Init() {
    HW_Machine::Init();
    
    OperatingSystem::CPU_Mediator();
    OperatingSystem::DMA_Mediator();
    OperatingSystem::HardDisk_Mediator();
    OperatingSystem::MMU_Mediator();
    OperatingSystem::Timer_Mediator();
    
    SetBootApplication(Application::DefaultBootApplication());
}


void OperatingSystem::ExecuteTestCode() {
    // INSERT HERE YOUR CODE
    // You can write a test code that will be executed and will invoke system calls or whenever you want
    //...
    
    // Process:exec();
    //...
}

 /*
  Not used
  */
 HW_MMU::Information OperatingSystem::asmm(std::string mnemonic) {
     HW_MMU::Information bincode;
     /* @TODO 
      */
     if (mnemonic == "Process:exec()") {
         bincode = 0xFFFFFFFF; // - (HW_CPU::addi<<24) + 
     }
     //@TODO
     bincode = (HW_CPU::addi<<26) + (HW_CPU::s0<<21) + (HW_CPU::s1<<16) + 1; // for tests purpose only
     return bincode;
 }