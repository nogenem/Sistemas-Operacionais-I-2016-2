/*
 * File:   Scheduler.h
 * Author: cancian
 *
 * Created on September 27, 2015, 11:19 AM
 */

#ifndef SCHEDULER_H
#define	SCHEDULER_H

#include <queue>

#include "Util_Scheduling_Queue.h"

template <typename T>
class Scheduler {
    friend class ProblemTester;
public:
    Scheduler();

    Scheduler(const Scheduler& orig) {

    }

    virtual ~Scheduler() {

    }
private:
    Scheduling_Queue<T>* _readyQueue;
    T* _choosen;
public:
    static const bool preemptive = true;
public:
    T* choose(); // choose a new schedulingItem to run
    T* choosen(); // returns the last choosen schedulingItem
    void reschedule();
    void insert(T* schedulingItem);
    T* remove(T* schedulingItem);
};

#endif	/* SCHEDULER_H */

