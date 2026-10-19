#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "Node.h"
#include "LogRecord.h"

class LogList {
public:
    DNode<LogRecord>* head;
    DNode<LogRecord>* tail;
    int count;
    
    long long comparaciones;
    int maxProfundidad;

    LogList() : head(nullptr), tail(nullptr), count(0), comparaciones(0), maxProfundidad(0) {}
    ~LogList() {
        DNode<LogRecord>* curr = head;
        while(curr) {
            DNode<LogRecord>* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void insertEnd(const LogRecord& val) {
        DNode<LogRecord>* n = new DNode<LogRecord>{val, nullptr, tail};
        if (tail) tail->next = n;
        else head = n;
        tail = n;
        count++;
    }

    int size() const { return count; }
    bool isEmpty() const { return count == 0; }

    void repararPunteros() {
        if (!head) {
            tail = nullptr;
            return;
        }
        DNode<LogRecord>* curr = head;
        curr->prev = nullptr;
        while (curr->next) {
            curr->next->prev = curr;
            curr = curr->next;
        }
        tail = curr;
    }

    DNode<LogRecord>* split(DNode<LogRecord>* h) {
        DNode<LogRecord>* fast = h;
        DNode<LogRecord>* slow = h;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        DNode<LogRecord>* temp = slow->next;
        slow->next = nullptr;
        return temp;
    }

    DNode<LogRecord>* merge(DNode<LogRecord>* first, DNode<LogRecord>* second, int depth) {
        if (depth > maxProfundidad) maxProfundidad = depth;
        if (!first) return second;
        if (!second) return first;

        comparaciones++;
        if (first->data < second->data || (!(second->data < first->data) && !(first->data < second->data))) {
            first->next = merge(first->next, second, depth + 1);
            return first;
        } else {
            second->next = merge(first, second->next, depth + 1);
            return second;
        }
    }

    DNode<LogRecord>* mergeSortAlg(DNode<LogRecord>* h, int depth) {
        if (depth > maxProfundidad) maxProfundidad = depth;
        if (!h || !h->next) return h;
        
        DNode<LogRecord>* second = split(h);
        h = mergeSortAlg(h, depth + 1);
        second = mergeSortAlg(second, depth + 1);
        
        return merge(h, second, depth + 1);
    }

    void sort() {
        comparaciones = 0;
        maxProfundidad = 0;
        head = mergeSortAlg(head, 1);
        repararPunteros();
    }
    
    bool isSorted() {
        if (!head) return true;
        DNode<LogRecord>* curr = head;
        while (curr->next) {
            if (curr->next->data < curr->data) return false;
            curr = curr->next;
        }
        return true;
    }
};

#endif // DOUBLYLINKEDLIST_H