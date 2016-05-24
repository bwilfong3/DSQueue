// Name: Ben Wilfong
// File Name: queue.h
// Date: 17 Nov, 2014
// Program Description:
//     This file contains the declarations
// of the Node structure and the queue ADT,
// all templatized for generic programming.


#ifndef QUEUE_H
#define QUEUE_H

template <class T>
struct Node
{
    Node<T>* next;
    T data;
};

template <class T>
class Queue
{
    private:
        Node<T>* front;
        Node<T>* rear;

    public:
        Queue();
        ~Queue();
        bool enqueue(T dataIn);
        bool dequeue(T& dataOut);
        bool isEmpty();
        int count;    
};

#include "queue.cpp"

#endif
