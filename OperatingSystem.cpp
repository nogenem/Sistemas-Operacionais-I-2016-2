/*
 * File:   System.cpp
 * Author: cancian
 *
 * Created on October 9, 2015, 9:04 PM
 */
#include <string>

#include "OperatingSystem.h"
#include "Application.h"
#include "HW_CPU.h"
#include "HW_Machine.h"
#include "Simulator.h"


void OperatingSystem::LoadApplication(Application* app, MMU::PhysicalAddress address) {
    Debug::cout(Debug::Level::trace, "OperatingSystem::LoadApplication(" + std::to_string(reinterpret_cast<unsigned long> (app)) + "," + std::to_string(address) + ")");
    std::list<Application::Information> code = app->getCode();
    HW_MMU::Information info;
    for(std::list<HW_MMU::Information>::iterator it = code.begin(); it != code.end(); it++) {
        info = (*it);
        HW_Machine::RAM()->write(address, info);
        address++;
    }    
}

void OperatingSystem::SetBootApplication(Application* app) {
    Debug::cout(Debug::Level::trace, "OperatingSystem::SetBootApplication(" + std::to_string(reinterpret_cast<unsigned long> (app)) + ")");
    HW_CPU::Register address = HW_Machine::CPU()->readRegister(HW_CPU::pc);
    LoadApplication(app, address);
}


void OperatingSystem::Init() {
    Debug::cout(Debug::Level::trace, "OperatingSystem::init()");
    HW_Machine::Init();
    
    OperatingSystem::CPU_Mediator();
    OperatingSystem::DMA_Mediator();
    OperatingSystem::HardDisk_Mediator();
    OperatingSystem::MMU_Mediator();
    OperatingSystem::Timer_Mediator();
    
    SetBootApplication(Application::DefaultBootApplication());  // load boot application into RAMs
}


void OperatingSystem::ExecuteTestCode() { 
    Debug::cout(Debug::Level::trace, "OperatingSystem::EXecuteTestCode()");
    Simulator* simulator = Simulator::getInstance();
    Entity* entity = simulator->getEntity();
    Module* module = simulator->getModule();
    int executionStep = std::stoi(entity->getAttribute("ExecutionStep")->getValue());
    double timeNow = simulator->getTnow();

    // INSERT HERE YOUR CODE
    // You can write a test code that will be executed and will invoke system calls or whenever you want
    // Follow the examples...
    // ...
    
    Scheduler<DiskAccessRequest>* scheduler;
	HW_HardDisk::DiskSector* diskSector;
	DiskAccessRequest *request;
	HardDisk* hd_mediator;

    switch (executionStep) {
        case 0:{  // ExecutionStep is initialized with 0
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(++executionStep)); // advance execution step
            simulator->insertEvent(timeNow + 10.0, module, entity); // future event when execution will advance

			// Adiciona os 2 jumps para fazer o disco sempre ir até as bordas
			scheduler = OperatingSystem::Disk_Scheduler();
			hd_mediator = OperatingSystem::HardDisk_Mediator();

			// Request para jump no track 0
			diskSector = new HW_HardDisk::DiskSector{{},0,0,0};
			request = new DiskAccessRequest(DiskAccessRequest::JUMP, 0, diskSector);
			scheduler->insert(request);

			// Request para jump no track maxTracks-1
			diskSector = new HW_HardDisk::DiskSector{{},0,hd_mediator->getTracksPerSurface()-1,0};
			request = new DiskAccessRequest(DiskAccessRequest::JUMP,0,diskSector);
			scheduler->insert(request);

			// Testes

			// Adicionar requisicoes de escrita/leitura ao escalonador de disco
			diskSector = new HW_HardDisk::DiskSector{{0,0,1,1},0,150,0};
			request = new DiskAccessRequest(DiskAccessRequest::WRITE,0,diskSector);
			scheduler->insert(request);

			diskSector = new HW_HardDisk::DiskSector{{1,1,1,1},0,50,0};
			request = new DiskAccessRequest(DiskAccessRequest::WRITE,0,diskSector);
			scheduler->insert(request);

			diskSector = new HW_HardDisk::DiskSector{{1,1},0,250,0};
			request = new DiskAccessRequest(DiskAccessRequest::WRITE,0,diskSector);
			scheduler->insert(request);

			// Pegar a 1* requisicao do escalonador
			request = scheduler->choose();

			// Chamar o Mediator_HardDisk passando esta primeira requisicao
			hd_mediator->accessBlock(request);
            break;
        }case 1:{
        	entity->getAttribute("ExecutionStep")->setValue(std::to_string(++executionStep)); // advance execution step

			scheduler = OperatingSystem::Disk_Scheduler();
			hd_mediator = OperatingSystem::HardDisk_Mediator();

			// Adicionar requisicoes de escrita/leitura ao escalonador de disco
			diskSector = new HW_HardDisk::DiskSector{{1,0,1,0},0,1,0};
			request = new DiskAccessRequest(DiskAccessRequest::WRITE,0,diskSector);
			scheduler->insert(request);
            break;
        }case 10:{
        	entity->getAttribute("ExecutionStep")->setValue(std::to_string(++executionStep)); // advance execution step

			scheduler = OperatingSystem::Disk_Scheduler();
			hd_mediator = OperatingSystem::HardDisk_Mediator();

			// Adicionar requisicoes de escrita/leitura ao escalonador de disco
			diskSector = new HW_HardDisk::DiskSector{{},0,250,0};
			request = new DiskAccessRequest(DiskAccessRequest::READ,0,diskSector);
			scheduler->insert(request);

			diskSector = new HW_HardDisk::DiskSector{{},0,50,0};
			request = new DiskAccessRequest(DiskAccessRequest::READ,0,diskSector);
			scheduler->insert(request);
			break;
        }case 20:{
			entity->getAttribute("ExecutionStep")->setValue(std::to_string(++executionStep)); // advance execution step

			scheduler = OperatingSystem::Disk_Scheduler();
			hd_mediator = OperatingSystem::HardDisk_Mediator();

			// Adicionar requisicoes de escrita/leitura ao escalonador de disco
			diskSector = new HW_HardDisk::DiskSector{{},0,1,0};
			request = new DiskAccessRequest(DiskAccessRequest::READ,0,diskSector);
			scheduler->insert(request);

			diskSector = new HW_HardDisk::DiskSector{{},0,150,0};
			request = new DiskAccessRequest(DiskAccessRequest::READ,0,diskSector);
			scheduler->insert(request);
			break;
        }default:{
            entity->getAttribute("ExecutionStep")->setValue(std::to_string(++executionStep)); // advance execution step
            break;
    	}
    }
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


void OperatingSystem::showStatistics(){
	HardDisk *disk = OperatingSystem::HardDisk_Mediator();
	std::cout << "\tDisk:\n";
	disk->showStatistics();
}
