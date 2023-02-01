/*using namespace std;
#include "List.h"

List::List() { size = 0; }

//List::~List() { }

bool List::add(ItemType item)
{
    Node* newNode = new Node;
    newNode->item = item;
    newNode->next = NULL;
    if (size == 0) {
        firstNode = newNode;
    }
    else {
        Node* current = firstNode;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
    return true;
}

bool List::add(int index, ItemType item)
{
    Node* newNode = new Node;
    if (index > -1 && index < size) {
        newNode->item = item;
        newNode->next = NULL;
        if (index == 0) {
            newNode->next = firstNode;
            firstNode = newNode;
        }
        else {
            Node* current = firstNode;
            for (int i = 1; i < index; index--) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
        return true;
    }
    else {
        return false;
    }
}

void List::remove(int index)
{
    if (index > -1 && index < size) {
        if (index == 0) {
            firstNode = firstNode->next;
        }
        else {
            Node* current = firstNode;
            Node* previous = current;
            for (index; index > 0; index--) {
                previous = current;
                current = current->next;
                previous->next = current->next;
            }
        }
        size--;
    }
}

void List::print()
{
    Node* current = firstNode;
    for (int i = 0; i <= size; i++) {
        if (current != NULL) {
            cout << "Name inside linked list is: ";
            cout << current->item << endl;
            current = current->next;
        }
    }
}*/