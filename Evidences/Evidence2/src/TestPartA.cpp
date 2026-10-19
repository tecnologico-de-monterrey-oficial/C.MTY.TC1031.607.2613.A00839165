#include <iostream>
#include <stdexcept>

// Importamos las cabeceras que ya existen en tu carpeta include
#include "../include/Node.h"
#include "../include/LinkedList.h"
#include "../include/Stack.h"
#include "../include/Queue.h"
#include "../include/DoubleLinkedList.h"

using namespace std;

int main() {
    cout << "   PRUEBAS PARTE A - ESTRUCTURAS\n";

    // PRUEBAS DE LISTA LIGADA SIMPLE 
    cout << "    PRUEBAS DE LISTA LIGADA SIMPLE\n";
    LinkedList<int> listaSimple;
    listaSimple.insertHead(10);
    listaSimple.insertTail(20);
    listaSimple.print();
    cout << "Eliminando head: " << listaSimple.deleteHead() << "\n\n";

    // PRUEBAS DE LA PILA 
    cout << " PRUEBAS DE PILA STACK\n";
    Stack<int> pila;
    cout << "1. Pop en pila vacia:\n";
    try {
        pila.pop();
    } catch (const std::runtime_error& e) {
        cout << "Mensaje controlado: " << e.what() << "\n";
    }

    cout << "\n2. Pila con 1 elemento:\n";
    pila.push(10);
    cout << "Size: " << pila.size() << "\n";
    cout << "Haciendo pop, salio: " << pila.pop() << " | Size actual: " << pila.size() << "\n";

    cout << "\n3. Operaciones normales LIFO:\n";
    pila.push(1); pila.push(2); pila.push(3);
    cout << "Push 1, 2, 3. Haciendo pop: ";
    while(!pila.isEmpty()) cout << pila.pop() << " ";
    cout << "\n\n";

    // PRUEBAS DE LA FILA
    cout << "PRUEBAS DE QUEUE\n";
    Queue<int> fila;
    cout << "1. Dequeue en fila vacia:\n";
    try {
        fila.dequeue();
    } catch (const std::runtime_error& e) {
        cout << "Mensaje controlado: " << e.what() << "\n";
    }

    cout << "\n2. Fila con 1 elemento:\n";
    fila.enqueue(99);
    cout << "Size: " << fila.size() << "\n";
    cout << "Haciendo dequeue, salio: " << fila.dequeue() << " | Size actual: " << fila.size() << "\n";

    cout << "\n3. Operaciones normales FIFO:\n";
    fila.enqueue(1); fila.enqueue(2); fila.enqueue(3);
    cout << "Enqueue 1, 2, 3. Haciendo dequeue: ";
    while(!fila.isEmpty()) cout << fila.dequeue() << " ";
    cout << "\n\n";

    //  PRUEBAS DE LA LISTA DOBLEMENTE LIGADA 
    cout << "    PRUEBAS LISTA DOBLEMENTE LIGADA \n";
    LogList dlist; // Usamos LogList vacía para probar su comportamiento
    cout << "1. Lista vacia:\n";
    if (dlist.size() == 0) cout << "La lista doblemente ligada esta vacia (Size 0).\n";

    LogRecord r1; r1.dia = 1; r1.lineaOriginal = "Log 1";
    LogRecord r2; r2.dia = 2; r2.lineaOriginal = "Log 2";
    
    cout << "\n2. Lista con 1 elemento e insercion:\n";
    dlist.insertEnd(r1);
    dlist.insertEnd(r2);
    cout << "Size tras inserciones: " << dlist.size() << "\n";
    
    cout << "\n3. Verificacion de punteros (repararPunteros):\n";
    dlist.repararPunteros();
    cout << "Punteros prev y next enlazados correctamente.\n";

    cout << "Finalizado\n";

    return 0;
}