//Julio Eduardo Rodriguez Ruiz A00839165
#include <iostream>
#include <cstdio>

int busquedaBinaria(const int arr[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    int datos[] = {3, 5, 6, 8, 11, 12, 13, 16, 27, 35};
    int n = sizeof(datos) / sizeof(datos[0]);
    int objetivo = 8;

    int resultado = busquedaBinaria(datos, n, objetivo);

    if (resultado != -1) {
        printf("Elemento encontrado en el indice: %d\n", resultado);
    } else {
        printf("Elemento no encontrado en el arreglo.\n");
    }

    return 0;
}