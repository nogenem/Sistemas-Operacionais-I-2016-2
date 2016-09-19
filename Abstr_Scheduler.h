/*
 * File:   Scheduler.h
 * Author: cancian
 *
 * Created on September 27, 2015, 11:19 AM
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include "Abstr_Thread.h"
#include "Util_Scheduling_Queue.h"

#include <queue>

class Scheduler {
    friend class ProblemTester;
public:
    Scheduler();

    Scheduler(const Scheduler& orig) {

    }

    virtual ~Scheduler() {

    }
private:
    Scheduling_Queue* _readyQueue;
    Thread* _choosen;
public:
    static const bool preemptive = true;
public:
    Thread* choose(); // choose a new thread to run
    Thread* choosen(); // returns the last choosen thread
    void reschedule();
    void insert(Thread* thread);
    Thread* remove(Thread* thread);
};

#endif	/* SCHEDULER_H */

