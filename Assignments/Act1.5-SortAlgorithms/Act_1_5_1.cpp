//Julio Eduardo Rodriguez Ruiz A00839165
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

int busquedaSecuencial(const std::vector<int>& vec, int objetivo) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == objetivo) {
            return i;
        }
    }
    return -1;
}

int busquedaBinaria(const std::vector<int>& vec, int objetivo) {
    int inicio = 0;
    int fin = vec.size() - 1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        if (vec[medio] == objetivo) {
            return medio;
        }
        if (vec[medio] < objetivo) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return -1;
}

void ejecutarPrograma1() {
    const int TAMANIO = 10000;
    std::vector<int> datos(TAMANIO);

    for (int i = 0; i < TAMANIO; ++i) {
        datos[i] = (std::rand() % 1000000) + 1;
    }

    std::sort(datos.begin(), datos.end());

    int numero = -1;
    while (true) {
        std::cout << "\nIngresa un numero entre 1 y 1,000,000 (0 para volver al menu): ";
        std::cin >> numero;

        if (numero == 0) {
            break;
        }

        clock_t inicioSec = clock();
        int posSec = busquedaSecuencial(datos, numero);
        clock_t finSec = clock();
        double tiempoSec = (double)(finSec - inicioSec) / CLOCKS_PER_SEC;

        clock_t inicioBin = clock();
        int posBin = busquedaBinaria(datos, numero);
        clock_t finBin = clock();
        double tiempoBin = (double)(finBin - inicioBin) / CLOCKS_PER_SEC;

        if (posBin != -1) {
            std::cout << "El numero " << numero << " SI se encuentra en el vector.\n";
        } else {
            std::cout << "El numero " << numero << " NO se encuentra en el vector.\n";
        }

        std::cout << "Tiempo de busqueda secuencial: " << tiempoSec << " segundos (" << (finSec - inicioSec) << " ticks)\n";
        std::cout << "Tiempo de busqueda binaria: " << tiempoBin << " segundos (" << (finBin - inicioBin) << " ticks)\n";
    }
}

void resolverCasoCaracterUnico(const std::string& s) {
    char carSec = s[s.length() - 1];
    int compSec = 0;
    
    for (size_t i = 0; i + 1 < s.length(); i += 2) {
        compSec++;
        if (s[i] != s[i + 1]) {
            carSec = s[i];
            break;
        }
    }

    char carBin = ' ';
    int compBin = 0;
    int inicio = 0;
    int fin = (static_cast<int>(s.length()) - 1) / 2;

    while (inicio <= fin) {
        compBin++;
        int medio = inicio + (fin - inicio) / 2;
        int idx = medio * 2;

        if (idx + 1 < static_cast<int>(s.length()) && s[idx] == s[idx + 1]) {
            inicio = medio + 1;
        } else {
            carBin = s[idx];
            fin = medio - 1;
        }
    }

    std::cout << carSec << " " << compSec << " " << carBin << " " << compBin << "\n";
}

void ejecutarPrograma2() {
    int n;
    std::cout << "\nIngresa la cantidad de cadenas (n): ";
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::string cadena;
        std::cin >> cadena;
        resolverCasoCaracterUnico(cadena);
    }
}

int main() {
    std::srand(std::time(NULL));

    int opcion = 0;
    do {
        std::cout << "\n MENU \n";
        std::cout << "1. Comparacion de Busqueda Secuencial vs Binaria (10,000 numeros)\n";
        std::cout << "2. Encontrar Caracter Unico en Strings (Conteo de comparaciones)\n";
        std::cout << "3. Salir\n";
        std::cout << "Selecciona una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            ejecutarPrograma1();
        } else if (opcion == 2) {
            ejecutarPrograma2();
        } else {
            std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 3);

    return 0;
}