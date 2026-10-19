#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
struct DNode {
    T data;
    DNode* next;
    DNode* prev;
};

#endif // NODE_H