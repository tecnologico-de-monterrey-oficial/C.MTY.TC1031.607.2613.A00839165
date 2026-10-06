//Julio Eduardo Rodriguez Ruiz A00839165
#include <iostream>
#include <string>
#include <stdexcept>
#include "Stack.h"

struct PaginaWeb {
    std::string titulo;
    std::string url;
};

int main() {
    Stack<PaginaWeb> historial;
    int opcion = 0;

    do {
        std::cout << "      SIMULADOR DE HISTORIAL WEB\n";
        std::cout << "1. Visitar una nueva pagina\n";
        std::cout << "2. Retroceder a la pagina anterior\n";
        std::cout << "3. Ver la pagina actual\n";
        std::cout << "4. Mostrar cuantas paginas hay en el historial\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opcion: ";

        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Entrada invalida. Intente de nuevo.\n";
            continue;
        }
        std::cin.ignore(10000, '\n');

        switch (opcion) {
            case 1: {
                PaginaWeb nuevaPagina;
                std::cout << "Ingrese el titulo de la pagina: ";
                std::getline(std::cin, nuevaPagina.titulo);
                std::cout << "Ingrese la URL de la pagina: ";
                std::getline(std::cin, nuevaPagina.url);
                historial.push(nuevaPagina);
                std::cout << "Pagina agregada al historial con exito.\n";
                break;
            }
            case 2: {
                try {
                    PaginaWeb cerrada = historial.pop();
                    std::cout << "Pagina cerrada: " << cerrada.titulo << " (" << cerrada.url << ")\n";
                    if (!historial.isEmpty()) {
                        PaginaWeb actual = historial.top();
                        std::cout << "Ahora estas en: " << actual.titulo << " (" << actual.url << ")\n";
                    } else {
                        std::cout << "El historial ha quedado vacio.\n";
                    }
                } catch (const std::underflow_error& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            case 3: {
                try {
                    PaginaWeb actual = historial.top();
                    std::cout << "Pagina actual:\n";
                    std::cout << "Titulo: " << actual.titulo << "\n";
                    std::cout << "URL: " << actual.url << "\n";
                } catch (const std::underflow_error& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            case 4: {
                std::cout << "Total de paginas en el historial: " << historial.size() << "\n";
                break;
            }
            case 5: {
                std::cout << "Saliendo del programa...\n";
                break;
            }
            default: {
                std::cout << "Opcion invalida. Ingrese un valor entre 1 y 5.\n";
                break;
            }
        }
    } while (opcion != 5);

    return 0;
}