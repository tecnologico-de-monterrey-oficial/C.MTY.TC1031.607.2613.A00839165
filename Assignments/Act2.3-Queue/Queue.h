#pragma once
#include <memory>
#include <stdexcept>
#include <utility>
#include "node.h"

template <typename T>
class Queue {
private:
    std::unique_ptr<Node<T>> head;
    Node<T>* tail;
    int size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    void push(const T& val) {
        auto newNode = std::make_unique<Node<T>>(val);
        Node<T>* rawNewNode = newNode.get();

        if (!head) {
            head = std::move(newNode);
            tail = rawNewNode;
        } else {
            tail->next = std::move(newNode);
            tail = rawNewNode;
        }
        size++;
    }

    T pop() {
        if (!head) {
            throw std::runtime_error("Excepcion: No se pudo borrar, el Queue esta vacio.");
        }

        T val = std::move(head->data);
        head = std::move(head->next);

        if (!head) {
            tail = nullptr;
        }

        size--;
        return val;
    }

    T front() const {
        if (!head) {
            throw std::runtime_error("Excepcion: No hay datos en el Queue.");
        }
        return head->data;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
};