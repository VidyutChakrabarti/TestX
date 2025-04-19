#include <iostream>
#include <string>
#include "linkedlist.h"
#include "coveragelogger.h"

using namespace std;

// Node class representing a single node in the linked list
Node::Node(string data) {
    this->data = data;
    this->next = nullptr;
}

Node::~Node() {
    if(this->next != nullptr) {
        delete(this->next);
    }
}

LinkedList::LinkedList() {
    head = nullptr;
}


LinkedList::~LinkedList() {
    if(head != nullptr) {
        delete(head);
    }
}

void LinkedList::append(string data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void LinkedList::printList() {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

void reverseLinkedList(LinkedList& list) {
    CoverageLogger::getInstance()->log(1u);
    Node* prev = nullptr;
    Node* current = list.head;
    Node* next = nullptr;
    
    while (current != nullptr) {
        CoverageLogger::getInstance()->log(2u);
        next = current->next;  // Store next node
        current->next = prev;  // Reverse current node's pointer
        prev = current;        // Move pointers one position ahead
        current = next;
    }
    CoverageLogger::getInstance()->log(3u);
    list.head = prev;  // Update head to new first node
}
