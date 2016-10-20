/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HD.h
 * Author: cancian
 *
 * Created on 29 de Agosto de 2016, 14:46
 */

#ifndef HD_H
#define HD_H

#include "HW_HardDisk.h"

class DiskAccessRequest {
public:
    enum Operation {READ, WRITE, JUMP};
public:
     DiskAccessRequest(Operation operation,HW_HardDisk::blockNumber blockNumber,
    		 HW_HardDisk::DiskSector* diskSector);

     HW_HardDisk::DiskSector* GetDiskSector() const {
         return _diskSector;
     }

     HW_HardDisk::blockNumber GetBlockNumber() const {
         return _blockNumber;
     }

     Operation GetOperation() const {
         return _operation;
     }

     void SetPriority(int _priority) {
         this->_priority = _priority;
     }

     int getPriority() const {
         return _priority;
     }

     double getArrivalTime() {
    	 return _arrivalTime;
     }

     /**
	   * Atualiza a prioridade desta requisição com base na posição
	   * atual do cabeçote do disco.
	   */
	 void updatePriority();
private:
    Operation _operation;
    HW_HardDisk::blockNumber _blockNumber;
    HW_HardDisk::DiskSector* _diskSector;
    int _priority; // this attribute MUST BE the one used to sort the Schelung_Queue, no matter the scheduler algorithm

    double _arrivalTime;//Tempo de chegada no sistema
};

class HardDisk {
    friend class ModuleInvoke_HardwareEvent;
    friend class ProblemTester;
public:
    HardDisk(unsigned int instance);
    HardDisk(const HardDisk& orig);
    virtual ~HardDisk();
public:
    void flush();

    /**
	 * Comanda o HD para executar uma Escrita ao bloco passado
	 * no @param request
	 * @param request Uma requisição com as informações necessarias
	 */
    void writeBlock(DiskAccessRequest* request);
    
    /**
	 * Comanda o HD para executar uma Leitura ao bloco passado
	 * no @param request
	 * @param request Uma requisição com as informações necessarias
	 */
    void readBlock(DiskAccessRequest* request);
    
    /**
	 * Chamada genérica que analisa a @param request para verificar que
	 * tipo de requisição é, e chamar o método adequado para trata-la
	 * @param request Uma requisição com as informações necessarias
	 */
    void accessBlock(DiskAccessRequest* request); // more generic than read or write. Invoke read or write inside it

    void setBlockSize(const unsigned int blocksize);

    /**
     * Returns the size of one disk block
     * @return The number of bytes per block
     */
    unsigned int getBlockSize();

    /**
     * Sets the maximum number of blocks per disk, used to define disk total space.
     * @param maxBlocks The maximum number of blocks per disk
     */
    void setMaxBlocks(const HW_HardDisk::blockNumber maxBlocks);

    /**
     * Returns the number of blocks per disk
     * @return The number of blocks per disk
     */
    HW_HardDisk::blockNumber getMaxBlocks();

    /**
	 * Comanda o HD para executar um Jump ao bloco passado
	 * no @param request
	 * @param request Uma requisição com as informações necessarias
	 */
	void jumpToBlock(DiskAccessRequest* request);

	/**
	 * Retorna a posição da 'head' do disco
	 * @return A posição da 'head' do disco
	 */
	unsigned int getHeadPosition();

	/**
	 * Retorna o numero de trilhas por superficie do disco
	 * @return O numero de trilhas por superficie do disco
	 */
	unsigned int getTracksPerSurface();
private:
    unsigned int _instance;
    unsigned int _blocksize;  // should be equal to the HD sector size for simplicity
    unsigned int _tracksPerSurface;
    HW_HardDisk::blockNumber _maxBlocks;
private:
    /**
	 * Trata a interrupção gerada pelo disco.
	 * Deve-se remover a ultima requisição atendida da lista do
	 * Escalonador, pedir ao Escalanador para escolher a próxima
	 * requisição e, caso haja uma, deve-se executa-la.
	 */
    static void interrupt_handler();
};

#endif /* HD_H */

