/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleInvoke_SystemCall.cpp
 * Author: cancian
 * 
 * Created on 18 de Setembro de 2016, 18:10
 */

#include "ModuleInvoke_SystemEvent.h"
#include "Simul_Entity.h"
#include "Simulator.h"

#include "OperatingSystem.h"
#include "Traits.h"

ModuleInvoke_SystemEvent::ModuleInvoke_SystemEvent(std::string name) : Module(name) {
    // ...
}

ModuleInvoke_SystemEvent::ModuleInvoke_SystemEvent(const ModuleInvoke_SystemEvent& orig) : Module(orig) {
}

ModuleInvoke_SystemEvent::~ModuleInvoke_SystemEvent() {
}

void ModuleInvoke_SystemEvent::do_run(Entity* entity) {
    std::string method = entity->getAttribute("MethodName")->getValue();

    if (method == "Timer::interrupt_handler()") {
        double interruptPeriod = Traits<HW_Timer>::timer_interrupt_period;
        Simulator* simulator = Simulator::getInstance();
        Entity* entity = simulator->getEntity();
        entity->getAttribute("MethodName")->setValue("Timer::interrupt_handler()");
        simulator->insertEvent(simulator->getTnow() + interruptPeriod, OperatingSystem::Module_SystemEvent(), entity);
    }

}
