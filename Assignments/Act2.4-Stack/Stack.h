#pragma once
#include "Node.h"
#include <memory>
#include <stdexcept>
#include <cstddef>

template <typename T>
class Stack {
private:
    std::unique_ptr<Node<T>> head;
    std::size_t count;

public:
    Stack() : head(nullptr), count(0) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    std::size_t size() const {
        return count;
    }

    void push(const T& val) {
        head = std::make_unique<Node<T>>(val, std::move(head));
        count++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Error: La pila esta vacia, no se puede hacer pop.");
        }
        T val = head->data;
        head = std::move(head->next);
        count--;
        return val;
    }

    T top() const {
        if (isEmpty()) {
            throw std::underflow_error("Error: La pila esta vacia, no hay elementos en el tope.");
        }
        return head->data;
    }
};