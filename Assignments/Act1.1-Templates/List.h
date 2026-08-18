#ifndef List_h
#define List_h

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class List {
private:
    vector<T> data;
    int size;
public:
    List();
    void insert(T val);
    void removeLast();
    T getData(int pos);
    int getSize();
    T getMax();
    void print();
    void insertAt(int pos, T val);
    void removeAt(int pos);
};

template <typename T>
List<T>::List() {
    size = 0;
}

template <typename T>
void List<T>::insert(T val) {
    data.push_back(val);
    size++;
}

template <typename T>
void List<T>::removeLast() {
    if (size == 0) {
        cout << "NO HAY ELEMENTOS" << endl;
    } else {
        cout << data[size - 1] << endl;
        data.pop_back();
        size--;
    }
}

template <typename T>
T List<T>::getData(int pos) {
    if (pos >= 0 && pos < size) {
        return data[pos];
    }
    throw out_of_range("POSICION INVALIDA");
}

template <typename T>
int List<T>::getSize() {
    return size;
}

template <typename T>
T List<T>::getMax() {
    if (size == 0) {
        throw out_of_range("NO HAY ELEMENTOS");
    }
    T maxVal = data[0];
    for (int i = 1; i < size; i++) {
        if (data[i] > maxVal) {
            maxVal = data[i];
        }
    }
    return maxVal;
}

template <typename T>
void List<T>::print() {
    for (int i = 0; i < size; i++) {
        cout << "[" << i << "] - " << data[i] << endl;
    }
}

template <typename T>
void List<T>::insertAt(int pos, T val) {
    if (pos < 0 || pos > size) {
        cout << "POSICION INVALIDA" << endl;
        return;
    }
    data.insert(data.begin() + pos, val);
    size++;
}

template <typename T>
void List<T>::removeAt(int pos) {
    if (size == 0) {
        cout << "NO HAY ELEMENTOS" << endl;
        return;
    }
    if (pos < 0 || pos >= size) {
        cout << "POSICIoN INVALIDA" << endl;
        return;
    }
    cout << data[pos] << endl;
    data.erase(data.begin() + pos);
    size--;
}

#endif /* List_h */
