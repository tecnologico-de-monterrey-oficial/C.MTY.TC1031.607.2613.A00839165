#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

struct Cliente {
    string nombre;
    int boletos;
};

int main() {
    Queue<Cliente> fila;
    int opcion = 0;

    while (opcion != 5) {
             << "1. Nuevo cliente\n"
             << "2. Atender cliente\n"
             << "3. Ver siguiente cliente\n"
             << "4. Cantidad en fila\n"
             << "5. Salir\n"
             << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Cliente c;
            cout << "Nombre: ";
            cin >> c.nombre;
            cout << "Boletos: ";
            cin >> c.boletos;
            fila.push(c);
            cout << "Cliente formado.\n";
        } 
        else if (opcion == 2) {
            try {
                Cliente c = fila.pop();
                cout << "Atendido: " << c.nombre << " con " << c.boletos << " boletos.\n";
            } catch (const runtime_error& e) {
                cout << e.what() << "\n";
            }
        } 
        else if (opcion == 3) {
            try {
                Cliente c = fila.front();
                cout << "Siguiente: " << c.nombre << " (" << c.boletos << " boletos).\n";
            } catch (const runtime_error& e) {
                cout << e.what() << "\n";
            }
        } 
        else if (opcion == 4) {
            cout << "Clientes en fila: " << fila.size() << "\n";
        }
    }

    return 0;
}