/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ModuleInvoke_PulseExecution.h
 * Author: cancian
 *
 * Created on 18 de Setembro de 2016, 12:06
 */

#ifndef MODULEINVOKE_PULSEEXECUTION_H
#define MODULEINVOKE_PULSEEXECUTION_H

#include "Module.h"

class ModuleInvoke_PulseExecution: public Module {
public:
    ModuleInvoke_PulseExecution(std::string name);
    ModuleInvoke_PulseExecution(const ModuleInvoke_PulseExecution& orig);
    virtual ~ModuleInvoke_PulseExecution();
private:
protected:
    virtual void do_run(Entity* entity);
};

#endif /* MODULEINVOKE_PULSEEXECUTION_H */

