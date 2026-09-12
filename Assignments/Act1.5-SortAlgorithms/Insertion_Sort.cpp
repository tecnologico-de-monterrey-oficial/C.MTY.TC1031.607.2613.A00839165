#include <iostream>
#include <vector>
#include <utility>

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}

void imprimirArreglo(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> datosInsertion = {29, 10, 14, 37, 13, 5, 22};
    std::vector<int> datosSelection = {64, 25, 12, 22, 11, 90, 42};
 
    std::cout << "Original: ";
    imprimirArreglo(datosInsertion);
    insertionSort(datosInsertion);
    std::cout << "Ordenado: ";
    imprimirArreglo(datosInsertion);

    std::cout << "Original: ";
    imprimirArreglo(datosSelection);
    selectionSort(datosSelection);
    std::cout << "Ordenado: ";
    imprimirArreglo(datosSelection);

    return 0;
}