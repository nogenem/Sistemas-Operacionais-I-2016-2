/*
 * File:   Scheduling_Queue.h
 * Author: cacian
 *
 * Created on October 9, 2015, 9:34 PM
 */

#ifndef SCHEDULING_QUEUE_H
#define	SCHEDULING_QUEUE_H

#include <queue>
#include <list>

template <typename T>
class Scheduling_Queue /* insert hierarchy if you want */ {
public:
    Scheduling_Queue();
    Scheduling_Queue(const Scheduling_Queue& orig);
    virtual ~Scheduling_Queue();
public:
    bool empty();
    void insert(T* t);
    void remove(T* t);
    void pop(); // remove the top (head) element
    T* top(); // returns the top (head) element
private:
    // INSERT YOUR CODE HERE
    // ...
    
    //std::priority_queue<T*>* _queue;
    std::list<T*>* _queue;
};

#endif	/* SCHEDULING_QUEUE_H */

