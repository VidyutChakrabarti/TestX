#ifndef LINKEDLIST
#define LINKEDLIST
#include <string>

using namespace std;

// Node class representing a single node in the linked list
class Node {
public:
    string data;
    Node* next;

    Node(string data);
    ~Node();
};

// LinkedList class to manage the linked list operations
class LinkedList {
public:
    Node* head;

    LinkedList();
    ~LinkedList();
    // Method to append a new node at the end of the list
    void append(string data);

    // Method to print the linked list
    void printList();

    friend std::ostream& operator<<(std::ostream&, LinkedList *&);
};

// Function to reverse a linked list
void reverseLinkedList(LinkedList& list);
#endif
