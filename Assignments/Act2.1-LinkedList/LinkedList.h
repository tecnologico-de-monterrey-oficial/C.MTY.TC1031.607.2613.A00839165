#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <stdexcept>
#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        size = 0;
    }

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    // Constructor de copia
    LinkedList(const LinkedList<T>& other) : head(nullptr), size(0) {
        *this = other;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    // 1. addFirst: Inserta al principio
    void addFirst(const T& data) {
        head = new Node<T>(data, head);
        size++;
    }

    // 2. addLast: Inserta al final
    void addLast(const T& data) {
        if (isEmpty()) {
            addFirst(data);
            return;
        }
        Node<T>* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new Node<T>(data);
        size++;
    }

    // 3. insert: Inserta después del índice dado
    void insert(int index, const T& data) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Índice fuera de rango para inserción.");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->next = new Node<T>(data, current->next);
        size++;
    }

    // 4. deleteData: Borra la primera coincidencia
    bool deleteData(const T& data) {
        if (isEmpty()) return false;

        if (head->data == data) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        Node<T>* current = head;
        while (current->next != nullptr && !(current->next->data == data)) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        return false;
    }

    // 5. deleteAt: Borra elemento en posición dada
    bool deleteAt(int index) {
        if (index < 0 || index >= size) return false;

        if (index == 0) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        Node<T>* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node<T>* temp = current->next;
        current->next = temp->next;
        delete temp;
        size--;
        return true;
    }

    // 6. getData: Obtiene dato en posición dada
    T getData(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Índice fuera de rango en getData.");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // 7. updateData: Actualiza el primer elemento igual al valor dado
    void updateData(const T& oldVal, const T& newVal) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == oldVal) {
                current->data = newVal;
                return;
            }
            current = current->next;
        }
        throw std::out_of_range("Elemento no encontrado en updateData.");
    }

    // 8. updateAt: Actualiza elemento en posición dada
    void updateAt(int index, const T& newVal) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Índice fuera de rango en updateAt.");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        current->data = newVal;
    }

    // 9. findData: Regresa posición del elemento o -1
    int findData(const T& data) const {
        Node<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->data == data) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    // 10. Sobrecarga operator[]: Lectura y escritura
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Índice fuera de rango en operator[].");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Índice fuera de rango en operator[] const.");
        }
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // 11. Sobrecarga operator=: Duplicación / Copia profunda
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this == &other) return *this;

        clear();
        Node<T>* otherCurrent = other.head;
        while (otherCurrent != nullptr) {
            addLast(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
        return *this;
    }

    // Despliegue de la lista
    void print() const {
        if (isEmpty()) {
            std::cout << "[Lista vacía]" << std::endl;
            return;
        }
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif /* LinkedList_h */