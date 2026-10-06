#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "NodeD.h"

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size = 0;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
};

template <typename T>
void DoublyLinkedList<T>::addFirst(T data) {
    // validamos si la lista está vacía
    if (head == nullptr) {
        // si está vacía la lista
        // apunto head a un nuevo nodo con data
        head = new NodeD<T>(data);
        // apunto tail a head
        tail = head;
        // incremento size
        size++;
    } else {
        // la lista no está vacía
        // creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        // apuntamos el next de aux a head
        aux->next = head;
        // apuntamos el prev de head a aux
        head->prev = aux;
        // apuntamos head a aux
        head = aux;
        // incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    // validamos si la lista está vacía
    if (head == nullptr) {
        // si está vacía la lista
        // apunto head a un nuevo nodo con data
        head = new NodeD<T>(data);
        // apunto tail a head
        tail = head;
        // incremento size
        size++;
    } else {
        // la lista no está vacía
        // creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        // apuntamos el prev de aux a tail
        aux->prev = tail;
        // apuntamos el next de tail a aux
        tail->next = aux;
        // apuntamos tail a aux
        tail = aux;
        // incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    // validamos que él índice sea válido
    if (index >= 0 && index <= size-1) {
        // validamos que el indice sea desde 0 hasta el penúltimo
        if (index != size-1) {
            // el index es desde 0 hasta el penúltimo (en medio)
            // creamos un indice auxiliar igual a 0
            int auxIndex = 0;
            // creamos un apuntador auxiliar igual a head
            NodeD<T>* aux = head;
            // iteramos hasta encontrar el índice dato
            while (auxIndex < index) {
                // recorremos aux
                aux = aux->next;
                // incrementamos el indice auxiliar
                auxIndex++;
            }
            // creamos un nodo nuevo
            NodeD<T>* auxNew = NodeD<T>(data);
            // el prev del nuevo lo apuntamos a aux
            auxNew->prev = aux;
            // el next del nuevo lo apuntamos a aux->next
            auxNew->next = aux->next;
            // el prev del siguiente de aux lo apuntamos al nuevo
            aux->next->prev = auxNew;
            // apuntamos aux next al nuevo
            aux->next = auxNew;
            // incrmenetamos size
            size++;
        } else {
            // el index es igual a size -1
            // hacemos como si fuera addLast
            // creamos un nuevo nodo
            NodeD<T>* aux = new NodeD<T>(data);
            // apuntamos el prev de aux a tail
            aux->prev = tail;
            // apuntamos el next de tail a aux
            tail->next = aux;
            // apuntamos tail a aux
            tail = aux;
            // incrementamos size
            size++;
        }
    } else {
        throw out_of_range("Índice inválido");
    }
}


#endif /* DoublyLinkedList_h */