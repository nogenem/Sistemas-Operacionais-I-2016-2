/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Application.h
 * Author: cancian
 *
 * Created on 31 de Agosto de 2016, 14:18
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include "HW_MMU.h"
#include "HW_CPU.h"

class Application {
public:
    typedef HW_MMU::Information Information;
public:
    Application();
    Application(const Application& orig);
    virtual ~Application();
public:
    void addCode(Information instruction);
    void addData(Information data);
    std::list<Information> getCode();
    std::list<Information> getData();
private:
    std::list<Information> _code;
    std::list<Information> _data;

public:

    static Application DefaultBootApplication() {
        Application app;
        HW_MMU::Information instruction;
        // 0: addi a0, zero, 0
        instruction = (HW_CPU::addi << HW_CPU::off_opcode) + (HW_CPU::a0 << HW_CPU::off_rd) + (HW_CPU::zero << HW_CPU::off_rs) + (0 << HW_CPU::off_const);
        app.addCode(instruction);
        // 1: syscall
        instruction = (HW_CPU::RType << HW_CPU::off_opcode) + (HW_CPU::syscall << HW_CPU::off_funct);
        app.addCode(instruction);
        // 2: addi a0, a0, 1
        instruction = (HW_CPU::addi << HW_CPU::off_opcode) + (HW_CPU::a0 << HW_CPU::off_rd) + (HW_CPU::a0 << HW_CPU::off_rs) + (1 << HW_CPU::off_const);
        app.addCode(instruction);
        // 3: j 1
        instruction = (HW_CPU::j << HW_CPU::off_opcode) + (1 << HW_CPU::off_addr);
        app.addCode(instruction);
        return app;
    }
};

#endif /* APPLICATION_H */

