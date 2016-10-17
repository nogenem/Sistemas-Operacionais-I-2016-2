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
#include "OperatingSystem.h"

HardDisk::HardDisk(unsigned int instance) {
	_instance = instance;
    HW_HardDisk* hd = HW_Machine::HardDisk();
    hd->setCommandRegister(HW_HardDisk::GET_SECTORSIZE);
    _blocksize = hd->getDataRegister();
    hd->setCommandRegister(HW_HardDisk::GET_TOTALSECTORS);
    _maxBlocks = hd->getDataRegister();
    hd->setCommandRegister(HW_HardDisk::GET_TRACKSPERSURFACE);
	_tracksPerSurface = hd->getDataRegister();
}

HardDisk::HardDisk(const HardDisk& orig) {
}

HardDisk::~HardDisk() {
}

void HardDisk::interrupt_handler() {     // Hard Disk Interrupt Handler
    // INSERT YOUR CODE HERE
    // ...
    
	HardDisk *hd = OperatingSystem::HardDisk_Mediator();
	Scheduler<DiskAccessRequest>* scheduler = OperatingSystem::Disk_Scheduler();
	DiskAccessRequest *request;
	unsigned int maxTracks = hd->getTracksPerSurface();

	// Remove a requisição que acabou de ser atendida
	request = scheduler->choosen();
	scheduler->remove(request);

	// Checa para ver se é um jump
	if(request->GetOperation() == DiskAccessRequest::JUMP){
		// Caso seja um Jump para track 0, deve-se atualizar
		// as prioridades das requisições na fila
		if(request->GetDiskSector()->track == 0){
			scheduler->reschedule();
		}

		// Jumps devem ter sua prioridade ajustada e devem ser adicionados denovo
		// na lista [fazendo a lista se reordenar]
		request->SetPriority(request->GetDiskSector()->track+maxTracks);
		scheduler->insert(request);
	}else{
		// Se não for um Jump apenas delete a requisição
		delete request;
	}

	// Pega a proxima requisição do escalonador e a executa
	request = scheduler->choose();
	std::cout << request->getPriority() << "\n";

	if(request != nullptr)
		hd->accessBlock(request);
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
	switch(request->GetOperation()){
	case DiskAccessRequest::READ:
		readBlock(request);
		break;
	case DiskAccessRequest::WRITE:
		writeBlock(request);
		break;
	case DiskAccessRequest::JUMP:
		jumpToBlock(request);
		break;
	default:
		break;
	}

	std::cout << "HardDisk::accessBlock(" << request << ")\n";
}

unsigned int HardDisk::getBlockSize() {
	return _blocksize;
}

void HardDisk::setMaxBlocks(const HW_HardDisk::blockNumber maxBlocks) {
    
}

HW_HardDisk::blockNumber HardDisk::getMaxBlocks() {
	return _maxBlocks;
}

void HardDisk::jumpToBlock(DiskAccessRequest* request){
	HW_HardDisk* hd = HW_Machine::HardDisk();
	HW_HardDisk::DiskSector* sector = request->GetDiskSector();
	//TODO rever esta conta
	hd->setDataRegister(sector->surface + sector->track + sector->sector);
	hd->setCommandRegister(HW_HardDisk::JUMP_TO_LOGICALSECTOR);
}

unsigned int HardDisk::getHeadPosition(){
    HW_HardDisk* hd = HW_Machine::HardDisk();
    hd->setCommandRegister(HW_HardDisk::GET_HEADTRACKPOSITION);
    return hd->getDataRegister();
}

unsigned int HardDisk::getTracksPerSurface(){
	return _tracksPerSurface;
}

void DiskAccessRequest::UpdatePriority(){
	HardDisk *hd = OperatingSystem::HardDisk_Mediator();
	unsigned int headPos = hd->getHeadPosition();
	unsigned int maxTracks = hd->getTracksPerSurface();
	unsigned int track = this->_diskSector->track;

	this->_priority = track + maxTracks;
	if(track >= headPos)//req.track esta a frente da head?
		this->_priority /= 2;//então aumenta a prioridade dela
}
