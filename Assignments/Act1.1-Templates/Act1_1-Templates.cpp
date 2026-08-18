#include <iostream>
#include <string>
#include "List.h"

using namespace std;

template <typename T>
T sum(T a, T b) {
    return a + b;
}

int main() {
    cout << "PRUEBAS CON ENTEROS" << endl;
    List<int> list;
    list.insert(5);
    list.insert(10);
    list.insert(15);
    list.print();
    
    cout << "\nProbando getSize(): " << list.getSize() << endl;
    
    cout << "\nProbando insertAt(1, 99):" << endl;
    list.insertAt(1, 99);
    list.print();
    
    cout << "\nProbando getMax(): " << list.getMax() << endl;
    cout << "Probando getData(2): " << list.getData(2) << endl;
    
    cout << "\nProbando removeAt(1):" << endl;
    list.removeAt(1);
    list.print();
    
    cout << "\nProbando removeLast():" << endl;
    list.removeLast();
    list.print();

    cout << "\nPRUEBAS CON STRINGS" << endl;
    List<string> things;
    things.insert("Laptop");
    things.insert("Bottle");
    things.print();
    
    cout << "\nProbando insertAt(0, Mouse):" << endl;
    things.insertAt(0, "Mouse");
    things.print();
    
    cout << "\nProbando error en removeAt(10):" << endl;
    things.removeAt(10);
    
    return 0;
}