#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <stdexcept>

template<typename T>
class Stack {
private:
    Node<T>* head;
    int count;
public:
    Stack() : head(nullptr), count(0) {}
    ~Stack() { while (!isEmpty()) pop(); }
    
    void push(T val) {
        Node<T>* n = new Node<T>{val, head};
        head = n;
        count++;
    }
    
    T pop() {
        if (!head) throw std::runtime_error("La pila esta vacia");
        Node<T>* temp = head;
        T val = temp->data;
        head = head->next;
        delete temp;
        count--;
        return val;
    }
    
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
};

#endif // STACK_H