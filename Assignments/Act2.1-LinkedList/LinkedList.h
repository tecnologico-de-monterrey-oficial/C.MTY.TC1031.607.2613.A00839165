#ifndef LinkedList_h
#define LinkedList_h

#include "Node.h"

template <typename T>
class LinkedList {
private:
    std:unique_ptr< Node<T> > head;
    int size;
public:
    LinkedList() : head(nullptr), size(0) {}
    void push_front(T data);
    void push_back(T data);
    void print();
};

template <typename T>
void LinkedList<T>::push_front(T data) {
    // crear un nodo nuevo
    std:unique_ptr< Node<T> > node = make_unique< Node<T> >(data);

    node->next = std::move(head);
    head = std::move(node);
}

template <typename T>
void LinkedList<T>::print() {
    node<T>* aux = head.get();
    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->next;
        if (aux != nullptr) {
            cout << " -> ";
        }
    }
    cout << endl;
}









#endif /* LinkedList_h */