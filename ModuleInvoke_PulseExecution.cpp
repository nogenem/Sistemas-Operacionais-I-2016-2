/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleInvoke_PulseExecution.cpp
 * Author: cancian
 * 
 * Created on 18 de Setembro de 2016, 12:06
 */

#include "ModuleInvoke_PulseExecution.h"

#include "Simulator.h"
#include "Simul_Debug.h"
#include "OperatingSystem.h"
#include "HW_Machine.h"

ModuleInvoke_PulseExecution::ModuleInvoke_PulseExecution(std::string name) : Module(name) {
}

ModuleInvoke_PulseExecution::ModuleInvoke_PulseExecution(const ModuleInvoke_PulseExecution& orig) : Module(orig) {
}

ModuleInvoke_PulseExecution::~ModuleInvoke_PulseExecution() {
}

void ModuleInvoke_PulseExecution::do_run(Entity* entity) { // virtual
    Simulator* simulator = Simulator::getInstance();
    Debug::cout(Debug::Level::info, this, entity, "Pulsing execution");

    //OperatingSystem::
    HW_Machine::CPU()->pulse();
    //Debug::cout(Debug::Level::fine, this, entity, "Entity will wait for " + std::to_string(delay) + " time units");

    Module* nextModule = *(this->_nextModules->begin());
    simulator->insertEvent(simulator->getTnow(), nextModule, entity);
}