#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <stdexcept>

template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    ~LinkedList() {
        while (head) deleteHead();
    }

    void insertHead(T val) {
        Node<T>* n = new Node<T>{val, head};
        head = n;
        if (!tail) tail = head;
        count++;
    }

    void insertTail(T val) {
        Node<T>* n = new Node<T>{val, nullptr};
        if (!tail) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        count++;
    }

    T deleteHead() {
        if (!head) throw std::out_of_range("Estructura vacia");
        Node<T>* temp = head;
        T val = temp->data;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        count--;
        return val;
    }

    T getHeadData() const {
        if (!head) throw std::out_of_range("Estructura vacia");
        return head->data;
    }

    int size() const { return count; }

    void print() const {
        Node<T>* curr = head;
        std::cout << "[ ";
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << "]\n";
    }
};

#endif // LINKEDLIST_H