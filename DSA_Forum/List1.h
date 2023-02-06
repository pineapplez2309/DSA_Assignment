// Testing purposes


/*#pragma once
#include<string>
#include<iostream>
using namespace std;

template< class T >
class Node {
public:
    T item;
    Node< T >* next;
};

template< class T >
class List {
public:
    int  empty();
    void add(T item);
    T    remove();
    void print();
    List() {
        firstnode = new Node< T >();
        firstnode->next = firstnode;
    }
private:
    int size;
    Node< T >* firstnode;
};

template< class T >
void List< T >::add(T item)
{
    Node< T >* p;

    p = new Node< T >();
    p->item = item;
    p->next = firstnode->next;
    firstnode->next = p;
}

template< class T >
T List< T >::remove()
{
    T item;
    Node< T >* node;

   
    node = firstnode->next;
    item = node->item;

    firstnode->next = node->next;
    delete node;

    return item;
}

template <class T>
void List<T>::print()
{
    T item;
    Node<T>* node;
    
    node = firstnode->next;
    

    while (node->item != NULL)
    {
        int i = 1;
        item = node->item;
        cout << i << ". " << item << "\n";       
        node = node->next;
        i++;
       
    }
}*/