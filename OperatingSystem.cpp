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
#include <list>


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
    
	Scheduler<DiskAccessRequest>* scheduler = OperatingSystem::Disk_Scheduler();
	HW_HardDisk::DiskSector* diskSector;
	DiskAccessRequest *request;

    // Adicionar requisicoes de escrita/leitura ao escalonador de disco
	//TODO rever isso
	diskSector = new HW_HardDisk::DiskSector{0,0,550,1};
	request = new DiskAccessRequest(DiskAccessRequest::WRITE,1,diskSector);
	scheduler->insert(request);

	diskSector = new HW_HardDisk::DiskSector{23,0,50,1};
	request = new DiskAccessRequest(DiskAccessRequest::WRITE,1,diskSector);
	scheduler->insert(request);

	diskSector = new HW_HardDisk::DiskSector{0,0,550,1};
	request = new DiskAccessRequest(DiskAccessRequest::READ,1,diskSector);
	scheduler->insert(request);

    // Pegar a 1* requisicao do escalonador
	request = scheduler->choose();

    // Chamar o Mediator_HardDisk passando esta primeira requisicao
	HardDisk* hd_mediator = OperatingSystem::HardDisk_Mediator();
	hd_mediator->accessBlock(request);
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
