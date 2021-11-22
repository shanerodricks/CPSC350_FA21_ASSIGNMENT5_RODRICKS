#ifndef LINKEDLIST_H //header guards
#define LINKEDLIST_H

#include <iostream>
#include <exception>
using namespace std;

template<class T>
class ListNode{
    public:
        ListNode();
        ListNode(T d);
        ~ListNode();
        ListNode<T> *next;
        ListNode<T> *prev;
        T data;
};

template<class T>
ListNode<T>::ListNode(){
    next = NULL;
    prev = NULL;
}

template<class T>
ListNode<T>::~ListNode(){}

template<class T>
ListNode<T>::ListNode(T d){
    data = d;
    next = NULL;
    prev = NULL;
}

template<class T>
class DoublyLinkedList{
    private:
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size;
    public:
        DoublyLinkedList();
        ~DoublyLinkedList();

        void insertFront(T d);
        void insertBack(T d);
        T removeFront();
        T removeBack();
        T returnFront();
        void printFront();
        void printBack();
        T removeNode(T value);
        T find(T value);
        bool isEmpty();
        unsigned int getSize();
        //void printList(bool isPrintLink);
};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(){
    front = NULL;
    back = NULL;
    size = 0;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList(){

}

template<class T>
bool DoublyLinkedList<T>::isEmpty(){
    if(front == NULL){
        //cout << "DLL Empty" << endl;
        return true;
    }
    else{
        //cout << "DLL NOT EMPTY" << endl;
        return false;
    }
}

template<class T>
void DoublyLinkedList<T>::printFront(){
    ListNode<T> *curr = front;
    while(curr != NULL){
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

template<class T>
void DoublyLinkedList<T>::printBack(){
    ListNode<T> *curr = back;
    while(curr != NULL){
        cout << curr->data << " ";
        curr = curr->prev;
    }
    cout << endl;

}

template<class T>
void DoublyLinkedList<T>::insertFront(T d){
    ListNode<T> *node = new ListNode<T>(d);
    if(isEmpty()){
        back = node;
    }
    else{//it is not empty
        node->next = front;
        front->prev = node;
    }
    front = node;
    ++size;
}

template<class T>
void DoublyLinkedList<T>::insertBack(T d){
    ListNode<T> *node = new ListNode<T>(d);
    //cout << "2 before" << endl;
    if(isEmpty()){
        front = node;
        //cout << "2 empty" << endl;
    }
    else{//it is not empty
        node->prev = back;
        back->next = node;
        //cout << "2 full" << endl;
    }
    back = node;
    //cout << "2" << endl;
    ++size;
}

template<class T>
T DoublyLinkedList<T>::removeFront(){
    if(isEmpty()){
        throw runtime_error("list is empty!");
    }

    ListNode<T> *temp = front;

    if(front->next == NULL){
        //only one node in the list and it's the front node
        back = NULL;
    }
    else{
        //more than one node in list
        front->next->prev = NULL;
    }

    front = front->next;
    temp->next = NULL;
    T data = temp->data;
    --size;
    delete temp;

    return data;
}

template<class T>
T DoublyLinkedList<T>::returnFront(){
    if(isEmpty()){
        throw runtime_error("list is empty");
    }
    return front->data; 
}

template<class T>
T DoublyLinkedList<T>::removeNode(T value){
    if(isEmpty()){
        throw runtime_error("list is empty");
    }
    //leverage the find method to decide wether we continue or not
    ListNode<T> *curr = front;
    while(curr->data != value){
        curr = curr->next;
        
        if(curr == NULL){
            return -1;
        }
    }

    //if it makes it here, we found the value
    //proceed to remove it

    if(curr == front){
        front = curr->next;
        front->prev = NULL;
    }
    if(curr == back){
        back = curr->prev;
        back->next = NULL;
    }
    if(curr != front && curr != back){
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
    }
    else if(curr == back){

    }
    else{

    }

}

template<class T>
unsigned int DoublyLinkedList<T>::getSize(){
    return size;

}


template<class T>
T DoublyLinkedList<T>::removeBack(){
    if(isEmpty()){
        throw runtime_error("list is empty!");
    }

    ListNode<T> *temp = back;
    if(back->prev == NULL){
        //only one node in the list
        front = NULL;
    }
    else{
        //more than one node in the list
        back->prev->next = NULL;
    }
    back = back->prev;
    temp->prev = NULL;
    int data = temp->data;
    --size;
    delete temp;

    return data;
}

#endif