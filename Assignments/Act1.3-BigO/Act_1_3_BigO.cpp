#include <iostream>
#include <vector>

using namespace std;

//FUNCION ITERATIVA
int sumaImparesIterativa(const vector<int>& vec) {
    int suma = 0;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] % 2 != 0) {
            suma += vec[i];
        }
    }
    return suma;
}

//FUNCION RECURSIVA
int sumaImparesRecursiva(const vector<int>& vec, int indice = 0) {
    if (indice >= vec.size()) {
        return 0;
    }
    int actual = (vec[indice] % 2 != 0) ? vec[indice] : 0;
    return actual + sumaImparesRecursiva(vec, indice + 1);
}

int main() {
    vector<int> numeros = {1, 2, 3, 4, 5, 6, 7};

    printf("Suma (Iterativa): %d\n", sumaImparesIterativa(numeros));
    printf("Suma (Recursiva): %d\n", sumaImparesRecursiva(numeros));

    return 0;
}