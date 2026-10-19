#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <stdexcept>

template<typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;
public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}
    ~Queue() { while (!isEmpty()) dequeue(); }
    
    void enqueue(T val) {
        Node<T>* n = new Node<T>{val, nullptr};
        if (!tail) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        count++;
    }
    
    T dequeue() {
        if (!head) throw std::runtime_error("La fila esta vacia");
        Node<T>* temp = head;
        T val = temp->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        count--;
        return val;
    }
    
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

#endif // QUEUE_H