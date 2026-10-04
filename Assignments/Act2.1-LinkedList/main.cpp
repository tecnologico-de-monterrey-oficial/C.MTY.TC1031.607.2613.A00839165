//Julio Eduardo Rodriguez Ruiz A00839165
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LinkedList.h"
#include "Fraction.h"

using namespace std;

// Funciones para pedir o generar datos de manera directa
int pedirDato(int) {
    int v;
    cout << "Valor (int): ";
    cin >> v;
    return v;
}

Fraction pedirDato(Fraction) {
    int n, d;
    cout << "Numerador y denominador: ";
    cin >> n >> d;
    return Fraction(n, d);
}

int randomDato(int) {
    return (rand() % 100) + 1;
}

Fraction randomDato(Fraction) {
    return Fraction((rand() % 20) + 1, (rand() % 20) + 1);
}

template <typename T>
void correrMenu() {
    LinkedList<T> list;
    LinkedList<T> copia;
    T dummy{};

    int modo, n;
    cout << "\n1. Capturar datos | 2. Aleatorios: ";
    cin >> modo;
    cout << "Cantidad de elementos iniciales: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        if (modo == 1) list.addLast(pedirDato(dummy));
        else list.addLast(randomDato(dummy));
    }

    int opc = -1;
    while (opc != 0) {
        cout << "\nLista: ";
        list.print();
        cout << "1.addFirst 2.addLast 3.insert 4.deleteData 5.deleteAt 6.getData\n"
             << "7.updateData 8.updateAt 9.findData 10.leer[] 11.modificar[] 12.duplicar(=) 0.Salir\n"
             << "Opcion: ";
        cin >> opc;

        try {
            int idx;
            if (opc == 1) {
                list.addFirst(pedirDato(dummy));
            } else if (opc == 2) {
                list.addLast(pedirDato(dummy));
            } else if (opc == 3) {
                cout << "Indice: "; cin >> idx;
                list.insert(idx, pedirDato(dummy));
            } else if (opc == 4) {
                cout << (list.deleteData(pedirDato(dummy)) ? "Borrado\n" : "No encontrado\n");
            } else if (opc == 5) {
                cout << "Posicion: "; cin >> idx;
                cout << (list.deleteAt(idx) ? "Borrado\n" : "Invalido\n");
            } else if (opc == 6) {
                cout << "Posicion: "; cin >> idx;
                cout << "Dato: " << list.getData(idx) << "\n";
            } else if (opc == 7) {
                cout << "Buscar: "; T val1 = pedirDato(dummy);
                cout << "Nuevo: "; T val2 = pedirDato(dummy);
                list.updateData(val1, val2);
            } else if (opc == 8) {
                cout << "Posicion: "; cin >> idx;
                list.updateAt(idx, pedirDato(dummy));
            } else if (opc == 9) {
                cout << "Posicion: " << list.findData(pedirDato(dummy)) << "\n";
            } else if (opc == 10) {
                cout << "Posicion: "; cin >> idx;
                cout << "Elemento: " << list[idx] << "\n";
            } else if (opc == 11) {
                cout << "Posicion: "; cin >> idx;
                list[idx] = pedirDato(dummy);
            } else if (opc == 12) {
                copia = list;
                cout << "Copia creada: ";
                copia.print();
            }
        } catch (const out_of_range& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int tipo;
    cout << "Tipo de lista (1. int, 2. Fraction): ";
    cin >> tipo;

    if (tipo == 1) correrMenu<int>();
    else if (tipo == 2) correrMenu<Fraction>();
    else cout << "Opcion invalida\n";

    return 0;
}