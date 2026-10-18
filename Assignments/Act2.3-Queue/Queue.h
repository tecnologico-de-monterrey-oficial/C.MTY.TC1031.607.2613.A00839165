#if !defined(Queue_h)
#define Queue_h

#include <stdexcept>
#include "Node.h"

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    Queue() : head(nullptr), tail(nullptr), count(0) {}
    ~Queue();

    bool isEmpty() const;
    int size() const;
    void push(T data);
    T pop();
    T front() const;
};

template <typename T>
Queue<T>::~Queue() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
int Queue<T>::size() const {
    return count;
}

template <typename T>
void Queue<T>::push(T data) {
    Node<T>* nuevo = new Node<T>(data);
    if (isEmpty()) {
        head = nuevo;
        tail = nuevo;
    } else {
        tail->next = nuevo;
        tail = nuevo;
    }
    count++;
}

template <typename T>
T Queue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("El Queue esta vacio. No se puede hacer pop.");
    }

    Node<T>* aux = head;
    T valor = aux->data;

    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next;
    }

    delete aux;
    count--;
    return valor;
}

template <typename T>
T Queue<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("El Queue esta vacio. No hay elementos al frente.");
    }
    return head->data;
}

#endif // Queue_h