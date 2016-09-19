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

class HardDisk {
    //friend class ModuleInvoke_InterruptHandler;
    friend class ProblemTester;
public:
    HardDisk();
    HardDisk(const HardDisk& orig);
    virtual ~HardDisk();
public:
    /**
     * Save structures in ram into disk
     */
    void flush();
    /**
     * Writes a block @param block into RAM structures
     * @param bn The number of the block to be written
     * @param block A pointer to the disk block.
     */
    void writeBlock(const HW_HardDisk::blockNumber bn, const HW_HardDisk::DiskSector* block);

    /**
     * Reads a block @param block
     * @param bn The number of the block to be read
     * @param block A pointer to the block
     */
    void readBlock(const HW_HardDisk::blockNumber bn, HW_HardDisk::DiskSector* block);

    /**
     * Sets the size of all blocks in the @class HardDisk
     * @param blocksize The number of bytes per block
     */
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


private:
    unsigned int blocksize;
    HW_HardDisk::blockNumber maxBlocks;
private:
    static void interrupt_handler();
};

#endif /* HD_H */

