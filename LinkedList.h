#ifndef SPOTIFY_LINKEDLIST_H
#define SPOTIFY_LINKEDLIST_H

#pragma once
#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class LinkedList{
public:
    struct Node{
        T data;
        Node* next;
        Node* prev;
    };
    //// PART 4 FUNCTIONS
    bool RemoveHead();
    bool RemoveTail();
    bool RemoveAt(unsigned int index);
    int Remove(const T& data);
    void Clear();

    void PrintForwardRecursive(Node* current);
    void PrintReverseRecursive(Node* current);



    //// PART 3 FUNCTIONS
    void InsertBefore(Node* node, const T& data);
    void InsertAfter(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);
    bool operator==(const LinkedList<T>& other) const;



    //// PART 2 FUNCTIONS
    Node* Head();  // done
    const Node* Head() const;  // done
    Node* Tail();  // done
    const Node* Tail() const;  // done

    Node* GetNode(unsigned int index);  // done
    const Node* GetNode(unsigned int index) const;  // done

    Node* Find(const T& data);  // done
    const Node* Find(const T& data) const;  // done

    void FindAll(vector<Node*>& other, const T& value);  // done

    T& operator[](unsigned int index);  // done
    const T& operator[](unsigned int index) const;  // done

    // COPY CONSTRUCTOR
    LinkedList(const LinkedList<T>& other);  // done
    // COPY ASSIGNMENT
    LinkedList<T> &operator=(const LinkedList<T>& other);  //done



    //// PART 1 FUNCTIONS
    LinkedList();

    Node* getHead();

    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T *data, unsigned int count);
    void AddNodesTail(const T *data, unsigned int count);

    unsigned int NodeCount();

    void PrintForward();
    void PrintReverse();

    ~LinkedList();
private:
    unsigned int removed_count;
    unsigned int count;
    unsigned int index;
    Node* head;
    Node* tail;

};

template<typename T>
bool LinkedList<T>::RemoveHead(){
    bool works = false;
    if (head == nullptr){
        return works;
    }
    if (count == 1){
        delete head;
        head = nullptr;
        tail = nullptr;
        count--;
        return works;
    }
    else{
        Node* current = head;
        head = current->next;
        if(head != nullptr){
            head->prev = nullptr;
            works = true;
        }
        delete current;
        count--;
        return works;
    }
}
//////////////////////////////////////////////// SAVED WORK///////////////////
template<typename T>
bool LinkedList<T>::RemoveTail(){
    bool works = false;
    if (tail == nullptr){
        return works;
    }
    else if(count == 1){
        delete tail;
        head = nullptr;  // added
        tail = nullptr;  // added
        count--;
        works = true;
    }
    else{
        Node* current = tail;
        tail = current->prev;

        if(tail != nullptr){
            tail->next = nullptr;
            works = true;
        }
        delete current;
        count--;
        return works;
    }
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index){
    if(index > count){
        return false;
    }
    if(index == 0){
        RemoveHead();
    }
    else if(index == count){
        RemoveTail();
    }
    else{
        Node* current = head;
        for(int i = 0; i < index; i++){
            current = current->next;
        }
        Node* prevNode = current->prev;
        Node* nextNode = current->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete current;
        count--;
    }
    return true;
}



template<typename T>
int LinkedList<T>::Remove(const T& data){
    Node* current = head;
    unsigned int removed_count = 0;
    while(current != nullptr){
        if(current->data == data){
            Node* prevNode = current->prev;
            Node* nextNode = current->next;
            if(prevNode != nullptr){
                prevNode->next = nextNode;
            }
            else{
                head = nextNode;
            }
            if(nextNode != nullptr){
                nextNode->prev = prevNode;
            }
            else{
                tail = prevNode;
            }
            Node* next = current->next;
            delete current;
            current = next;
            count--;
            removed_count++;

        }
        else{
            current = current->next;
        }
    }
    return removed_count;
}

template<typename T>
void LinkedList<T>::Clear(){
    Node* current = head;
    while(current != nullptr){
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(Node* current){
    if(current == nullptr){
        return;
    }
    cout << current->data << endl;
    PrintForwardRecursive(current->next);
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(Node* current){
    if(current == nullptr){
        return;
    }
    cout << current->data << endl;
    PrintReverseRecursive(current->prev);
}




/////////////////////////  PART 3 FUNCTIONS  ////////////////////////////////
template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data){
    Node* newNode = new Node;
    newNode->data = data;

    newNode->next = node;
    newNode->prev = node->prev;

    Node* prevNode = node->prev;
    prevNode->next = newNode;

    node->prev = newNode;
    count++;
}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data){
    Node* newNode = new Node;
    newNode->data = data;

    newNode->prev = node;
    newNode->next = node->next;

    Node* nextNode = node->next;
    nextNode->prev = newNode;

    node->next = newNode;
    count++;
}

template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index){
    if(index > count){
        throw out_of_range("Error: Out of Range");
    }

    Node* newNode = new Node;
    newNode->data = data;

    if(index == 0){  // first one in list
        newNode->next = head;
        newNode->prev = nullptr;
        if (head != nullptr) {
            head->prev = newNode;
        }
        else {  // if is empty newNode become tail and head
            tail = newNode;
            head = newNode;
        }
        head = newNode;
    }
    else if(index == count){  // last one in list
        newNode->prev = tail;
        newNode->next = nullptr;
        if (tail != nullptr) {
            tail->next = newNode;
        }
        else {
            head = newNode;
            tail = newNode;
        }
        // tail = newNode;
    }
    else{  // anywhere in the middle of linked list
        Node* current = head;
        for(int i = 0; i < index; i++){
            current = current->next;
        }
        newNode->next = current;
        newNode->prev = current->prev;

        Node* prevNode = current->prev;
        prevNode->next = newNode;

        current->prev = newNode;
    }
    count++;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& other) const{
    Node* current = head;
    Node* current2 = other.head;
    while(current != nullptr){
        if(current->data != current2->data){
            return false;
        }
        current = current->next;
        current2 = current2->next;
    }
    return true;
}



//////////////////////////////  PART 2 FUNCTIONS  ///////////////////////////////////////
template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head(){
    Node* current = head;  // set the current to head
    return current;  // return the current which is pointing to head
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const{  // same as function above
    Node* current = head;
    return current;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail(){
    Node* current = tail;  // set the current to the tail
    return current;  // return the current which is pointing to tail
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const{  // same as function above
    Node* current = tail;
    return current;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index){
    if(index >= count){
        throw out_of_range("Index Out of Range!");  // throw error if out of range
    }
    Node* current = head;  // set the current to head or beginning of linked list
    for(int i = 0; i < index; i++){  // iterate though the linked list
        current = current->next;  // after each iteration move to next node in list
    }
    return current;  // return
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const{  // same as function above
    if(index >= count){
        throw out_of_range("Index Out of Range!");
    }
    Node* current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    return current;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data){
    Node* current = head;  // set the current to head or beginning of the linked list
    while(current != nullptr){  // continue loop until empty or end of linked list
        if(current->data == data){  // check if data in node matches passes in data
            return current;  // return pointer to node
        }
        current = current->next;  // move onto next node after each iteration
    }
    return nullptr;  // return null if not found
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const{  // same as the function above
    Node* current = head;
    while(current != nullptr){
        if(current->data == data){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& other, const T &value){
    Node* current = head;  // set current to head or beginning of linked list
    while(current != nullptr){  // continue loop until empty or end of list
        if(current->data == value){  // check if data in node matches passed in data
            other.push_back(current);  // add that value to vector
        }
        current = current->next;  // move onto next node after each iteration
    }
}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index){
    if(index >= count){  // check if index out of range
        throw out_of_range("Index our of Range");  // throw error
    }
    Node* current = head;  // set current to head or beginning of linked list
    for(int i = 0; i < index; i++){  // loop through the entire list until passed in index value times
        current = current->next;  // move onto next node after each iteration
    }
    return current->data;  // return data at current node
}


template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const{  // same as function above
    if(index >= count){
        throw out_of_range("Index our of Range");
    }
    Node* current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    return current->data;
}


// COPY CONSTRUCTOR
template<typename T>
LinkedList<T>::LinkedList(const LinkedList& other){
    this->count = 0;  // set count to same as default constructor
    this->head = nullptr;  // set to same as default constructor
    this->tail = nullptr;  // set to same as default constructor

    Node* current = other.head;  // create copy
    while(current != nullptr){  // loop through until empty or end of linked list
        AddTail(current->data);  // add value to end of linked list to match up accodingly
        current = current->next;  // move onto next node after each iteration
    }
}

// COPY ASSIGNMENT
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other){ // about same as function
    Node* current = head;                                              // but deleting nodes before
    while(current != nullptr){                                         // assigning
        Node* current2 = current->next;
        delete current;
        current = current2;
    }

    this->count = 0;
    this->head = nullptr;
    this->tail = nullptr;

    current = other.head;
    while(current != nullptr){
        AddTail(current->data);
        current = current->next;
    }
    return *this;
}




///////////////////////////////  PART 1 FUNCTIONS  /////////////////////////////////
template<typename T>
LinkedList<T>::LinkedList(){
    count = 0;
    head = nullptr;  // start with head set to null
    tail = nullptr;  // start with tail set to null
}                  // ^^^ starting with empty


template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHead(){
    return head;
}

template<typename T>
void LinkedList<T>::AddHead(const T& data){
    Node* newNode = new Node;  // create new node
    newNode->data = data;  // attach passed in data with that new node
    newNode->next = head;  // set next of new point to point to old head
    newNode->prev = nullptr;  // new head points to null since nothing preceeds it
    if(head != nullptr){  // if not empty
        head->prev = newNode;  // the prev pointer of current node is set to newNode
    }
    else{  // if empty
        tail = newNode;  // empty so newNode also becomes the tail
    }
    head = newNode;  // update the newNode to be head
    count++;  // increase count by 1
}

template<typename T>
void LinkedList<T>::AddTail(const T& data){
    Node* newNode = new Node;  // create new node
    newNode->data = data;  // attach passed in data with that new node
    newNode->next = nullptr;  // tail next points to null ptr since nothing is after tail
    if(tail != nullptr){  //if not empty
        newNode->prev = tail;  // prev pointer of newNode is set the the old tail
        tail->next = newNode;  // old tail nexts points that new node
        tail = newNode; // set that new node to tail
    }
    else{  // if empty
        head = newNode;  // since empty the head is new node and tail is also new node
        tail = newNode;
        newNode->prev = nullptr;  // prev points to null since only one node would be in
    }
    count++;  // increase count by 1
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count){
    for(unsigned int i = 0; i < count; i++){ // loops though all the elements of passed array
        AddHead(data[i]);  // create a new head node for each element of that pass in array
    }
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count){
    for(unsigned int i = 0; i < count; i++){ // loops though all the elements of passed array
        AddTail(data[i]);  // create a new head node for each element of that pass in array
    }
}

template<typename T>
unsigned int LinkedList<T>::NodeCount(){
    return count;
}

template<typename T>
void LinkedList<T>::PrintForward(){
    Node* current = head;  // set current to the head or the beginning of the linked list
    for(int i = 0; i < count; i++){  // loop though the entire linked list.
        cout << current->data << endl; // print the data of current node
        current = current->next;  // after each iteration chnage the current to the next in line
    }
}

template<typename T>
void LinkedList<T>::PrintReverse(){
    // cout << "Test" << endl;
    Node* current = tail;  // set the current to the tail or the end of the linked lists
    while(current != nullptr){  // loop through the entire linked lists
        cout << current->data << endl;  // print the data of the current node
        current = current->prev;  // after each iteration cahnge the current to the prev in line
    }
}

// destructor (remove the nodes)
template<typename T>
LinkedList<T>::~LinkedList(){
    Node* current = head;  // set the current to the head or the beginning of the linked list
    while (current != nullptr) {  // while current is not empty
        Node* next = current->next;  // set next the the next node in line
        delete current; // delete the current node
        current = next; // move on to the next in line
    }
}

#endif //SPOTIFY_LINKEDLIST_H
