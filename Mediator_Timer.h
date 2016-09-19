/*
 * File:   TimerMediator.h
 * Author: cancian
 *
 * Created on October 9, 2015, 2:55 PM
 */

#ifndef TIMERMEDIATOR_H
#define	TIMERMEDIATOR_H

//#include "ModuleInvoke_InterruptHandler.h"

class Timer {
    friend class ModuleInvoke_InterruptHandler;
    friend class ProblemTester;
private:

    Timer() {
    }

    Timer(const Timer& orig) {
    }

    virtual ~Timer() {
    }
private:
    static void interrupt_handler();
};

#endif	/* TIMERMEDIATOR_H */

