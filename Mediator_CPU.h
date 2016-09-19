/*
 * File:   CPU.h
 * Author: cancian
 *
 * Created on October 10, 2015, 1:58 AM
 */

#ifndef CPU_H
#define	CPU_H

#include "Abstr_Thread.h"

class CPU {
private:
    CPU(unsigned int instance);
    CPU(const CPU& orig);
    virtual ~CPU();
public:
    static void switch_context(Thread* previous, Thread* next);
    static void restore_context(Thread* next);
    //void switch_context(Thread* previous, Thread* next);
    //void restore_context(Thread* next);
    static unsigned int getInstance();
    static void setInstance(unsigned int _instance);
    
private:
    static unsigned int _instance;
};

#endif	/* CPU_H */

