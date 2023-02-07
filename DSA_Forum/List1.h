// Testing purposes


#pragma once
#include<string>
#include<iostream>
using namespace std;



template< class T >
class List {
private:
    struct Node {
        T item;
        Node* next;
    };
    int size;
    Node* firstNode;

public:
    int  empty();
    bool add(T item);
    void remove(int index);
    void print();
    List() { List::size = 0; }
    int getLength();
};

template< class T >
bool List< T >::add(T item)
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

template< class T >
void List< T >::remove(int index)
{
    bool success = (index >= 0) && (index < size);
    if (success)
    {
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

template <class T>
int List<T>::getLength() { return size; }

template <class T>
void List<T>::print()
{
    /*T item;
    Node<T>* node;
    int i = 1;
    node = firstnode->next;
    

    while (node->item != NULL)
    {      
        item = node->item;
        cout << i << ". " << item << "\n";       
        node = node->next;
        i++;
       
    }*/
    Node* current = firstNode;
    for (int i = 1; i <= size + 1; i++) {
        if (current != NULL) {
            cout << i << ". ";
            cout << current->item << endl;
            current = current->next;
        }
    }
}