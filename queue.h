#ifndef GENQUEUE_H
#define GENQUEUE_H

#include <iostream>
#include <exception>
#include "linkedList.h"

using namespace std;

template<class T>
class GenQueue{
    public:
        GenQueue(); //default constructor
        ~GenQueue();
        
        //core functions
        void insert(T data); //aka enqueue()
        T remove(); //aka dequeue()

        //auxilary functions
        T peek(); //peek
        bool isFull();
        bool isEmpty();
        unsigned int getSize(); //unsigned variable: will not be negative (8 bytes); can also replace size_t with "size_t"
        void printArray();
    
    private:
        DoublyLinkedList<T> *listQueue;
};

template<class T>
GenQueue<T>::GenQueue(){
    listQueue = new DoublyLinkedList<T>();
}

template<class T>
GenQueue<T>::~GenQueue(){
    delete listQueue;
}

template<class T>
void GenQueue<T>::insert(T data){
    listQueue->insertBack(data);
}

template<class T>
T GenQueue<T>::remove(){
    if(isEmpty()){
        throw runtime_error("remove:queue is empty");
    }
    //char c = '\0'; null value
    T returnedData = listQueue->removeFront();
    return returnedData;
}

template<class T>
T GenQueue<T>::peek(){
    if(isEmpty()){
        throw runtime_error("peek:queue is empty");
    }
    return listQueue->returnFront();
}


template<class T>
bool GenQueue<T>::isFull(){
    return false;
}

template<class T>
bool GenQueue<T>::isEmpty(){
    return listQueue->isEmpty();
}

template<class T>
unsigned int GenQueue<T>::getSize(){
    return listQueue->getSize();
}




#endif