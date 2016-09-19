/*
 * File:   System.h
 * Author: cancian
 *
 * Created on October 9, 2015, 9:04 PM
 */

#ifndef SYSTEM_H
#define	SYSTEM_H

#include "Abstr_Scheduler.h"
#include "Abstr_MemoryManager.h"
#include "Abstr_FileSystem.h"
#include "Traits.h"

#include "ModuleInvoke_SystemEvent.h"

#include "Application.h"

class OperatingSystem {
private:

    OperatingSystem() {

    }

    OperatingSystem(const OperatingSystem& orig) {

    }

    virtual ~OperatingSystem() {

    }
public:

    static Scheduler* Process_Scheduler() {
        static Scheduler* _processScheduler;
        if (_processScheduler == nullptr) {
            _processScheduler = new Scheduler();
        }
        return _processScheduler;
    }

    static FileSystem* File_System() {
        static FileSystem* _fileSystem;
        if (_fileSystem == nullptr) {
            _fileSystem = new FileSystem();
        }
        return _fileSystem;
    }

    static Scheduler* Disk_Scheduler() {
        static Scheduler* _diskScheduler;
        if (_diskScheduler == nullptr) {
            _diskScheduler = new Scheduler();
        }
        return _diskScheduler;
    }

    static MemoryManager* Memory_Manager() {
        static MemoryManager* _memoryManager;
        if (_memoryManager == nullptr) {
            _memoryManager = new MemoryManager();
        }
        return _memoryManager;
    }
  
    static ModuleInvoke_SystemEvent* Module_SystemEvent() {
        static ModuleInvoke_SystemEvent* _moduleSystemEvent;
        if (_moduleSystemEvent == nullptr) {
            _moduleSystemEvent = new ModuleInvoke_SystemEvent("SystemEvent");
        }
        return _moduleSystemEvent;
    }
    
    static Application CreateDefaultApplication();
    static void SetBootApplication(Application app);
    static void Init();
    
private:
    static HW_MMU::Information asmm(std::string mnemonic);
};

#endif	/* SYSTEM_H */

