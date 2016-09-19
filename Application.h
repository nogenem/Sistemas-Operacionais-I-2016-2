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
};

#endif /* APPLICATION_H */

