/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HD.cpp
 * Author: cancian
 * 
 * Created on 29 de Agosto de 2016, 14:46
 */

#include "Mediator_HardDisk.h"
#include "HW_Machine.h"

HardDisk::HardDisk(unsigned int instance) {
    _instance = instance;
    HW_HardDisk* hd = HW_Machine::HardDisk();
    hd->setCommandRegister(HW_HardDisk::GET_SECTORSIZE);
    _blocksize = hd->getDataRegister();
    hd->setCommandRegister(HW_HardDisk::GET_TOTALSECTORS);
    _maxBlocks = hd->getDataRegister();
}

HardDisk::HardDisk(const HardDisk& orig) {
}

HardDisk::~HardDisk() {
}

void HardDisk::interrupt_handler() {     // Hard Disk Interrupt Handler
    // INSERT YOUR CODE HERE
    // ...

	Scheduler<DiskAccessRequest>* scheduler = OperatingSystem::Disk_Scheduler();
	DiskAccessRequest *request;

    // Pega a proxima requisicao do escalonador e a executa
	request = scheduler->choose();
	this->accessBlock(request);
}

void HardDisk::flush() {
    
}

void HardDisk::writeBlock(DiskAccessRequest* request) {
	HW_HardDisk* hd = HW_Machine::HardDisk();
	HW_HardDisk::DiskSector* sector = request->GetDiskSector();
	//TODO rever esta conta
	hd->setDataRegister(sector->surface + sector->track + sector->sector);
	hd->setStreamRegister(sector->data);
	hd->setCommandRegister(HW_HardDisk::WRITE_LOGICALSECTOR);
}


void HardDisk::readBlock(DiskAccessRequest* request) {
	HW_HardDisk* hd = HW_Machine::HardDisk();
	HW_HardDisk::DiskSector* sector = request->GetDiskSector();
	//TODO rever esta conta
    hd->setDataRegister(sector->surface + sector->track + sector->sector);
    hd->setCommandRegister(HW_HardDisk::READ_LOGICALSECTOR);
}

void HardDisk::setBlockSize(const unsigned int blocksize) {
    
}

void HardDisk::accessBlock(DiskAccessRequest* request) {
    if (request->GetOperation() == DiskAccessRequest::READ) {
        readBlock(request);
    } else {
        writeBlock(request);
    }
        
}

unsigned int HardDisk::getBlockSize() {
    return _blocksize;
}

void HardDisk::setMaxBlocks(const HW_HardDisk::blockNumber maxBlocks) {
    
}

HW_HardDisk::blockNumber HardDisk::getMaxBlocks() {
    return _maxBlocks;
}
