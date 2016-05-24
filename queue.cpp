// Name: Ben Wilfong
// File Name: queue.cpp
// Date 17 Nov, 2014
// Program Description:
//     This file contains the definitions
// of the functions found in the queue ADT,
// all templatized for generic programming.


#ifndef QUEUE_CPP
#define QUEUE_CPP

template <class T>
Queue<T> :: Queue()
{
    front = NULL;
    rear  = NULL;
    count = 0;
}

template <class T>
bool Queue<T> :: enqueue(T dataIn)
{
    Node<T>* pNew = new Node<T>;
    pNew->data = dataIn;
    pNew->next = NULL;

    if (front == NULL)
       front = rear = pNew;

    else
    {
       rear->next = pNew;
       rear = pNew;
    }
    
    count++;
    return true;
}

template <class T>
bool Queue<T> :: dequeue(T& dataOut)
{
    if (count == 0)
        return false; // empty queue

    Node<T>* temp = front;
    dataOut = temp->data;
    front = front->next;

    if (front == NULL)
        rear = NULL;

    delete temp;

    count--;

    return true;
}

template <class T>
bool Queue<T> :: isEmpty()
{
    return (count == 0);
}

template <class T>
Queue<T> :: ~Queue()
{
    T junk;
    while(this->dequeue(junk));
}
#endif
