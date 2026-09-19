//A00839165 Julio Eduardo Rodriguez Ruiz
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;
using namespace std::chrono;

struct Metrics {
    long long comparisons = 0;
    long long swaps = 0;
    long long duration_ns = 0;
};

// ALGORITMOS DE ORDENAMIENTO

// 1. Swap Sort (Intercambio directo clásico)
template <typename T>
Metrics swapSort(vector<T>& arr) {
    Metrics m;
    auto start = high_resolution_clock::now();
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            m.comparisons++;
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
                m.swaps++;
            }
        }
    }
    auto end = high_resolution_clock::now();
    m.duration_ns = duration_cast<nanoseconds>(end - start).count();
    return m;
}

// 2. Selection Sort
template <typename T>
Metrics selectionSort(vector<T>& arr) {
    Metrics m;
    auto start = high_resolution_clock::now();
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            m.comparisons++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(arr[i], arr[min_idx]);
            m.swaps++;
        }
    }
    auto end = high_resolution_clock::now();
    m.duration_ns = duration_cast<nanoseconds>(end - start).count();
    return m;
}

// 3. Bubble Sort
template <typename T>
Metrics bubbleSort(vector<T>& arr) {
    Metrics m;
    auto start = high_resolution_clock::now();
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            m.comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                m.swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    auto end = high_resolution_clock::now();
    m.duration_ns = duration_cast<nanoseconds>(end - start).count();
    return m;
}

// 4. Insertion Sort
template <typename T>
Metrics insertionSort(vector<T>& arr) {
    Metrics m;
    auto start = high_resolution_clock::now();
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            m.comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                m.swaps++; // Representa el desplazamiento de elemento
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
    auto end = high_resolution_clock::now();
    m.duration_ns = duration_cast<nanoseconds>(end - start).count();
    return m;
}

// 5. Merge Sort
template <typename T>
void merge(vector<T>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

template <typename T>
void mergeSortHelper(vector<T>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

template <typename T>
Metrics mergeSort(vector<T>& arr) {
    Metrics m;
    auto start = high_resolution_clock::now();
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, arr.size() - 1);
    }
    auto end = high_resolution_clock::now();
    m.duration_ns = duration_cast<nanoseconds>(end - start).count();
    return m;
}

// 6. Quick Sort
template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quickSortHelper(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

template <typename T>
Metrics quickSort(vector<T>& arr) {
    Metrics m;
    auto start = high_resolution_clock::now();
    if (!arr.empty()) {
        quickSortHelper(arr, 0, arr.size() - 1);
    }
    auto end = high_resolution_clock::now();
    m.duration_ns = duration_cast<nanoseconds>(end - start).count();
    return m;
}

// 7. Extra: Shell Sort
template <typename T>
Metrics shellSort(vector<T>& arr) {
    Metrics m;
    auto start = high_resolution_clock::now();
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    auto end = high_resolution_clock::now();
    m.duration_ns = duration_cast<nanoseconds>(end - start).count();
    return m;
}

// GENERADORES DE DATOS ALEATORIOS

mt19937 rng(1337); // Semilla fija para reproducibilidad

vector<int> generateRandomInt(size_t size) {
    vector<int> v(size);
    uniform_int_distribution<int> dist(-1000000, 1000000);
    for (size_t i = 0; i < size; ++i) v[i] = dist(rng);
    return v;
}

vector<double> generateRandomDouble(size_t size) {
    vector<double> v(size);
    uniform_real_distribution<double> dist(-10000.0, 10000.0);
    for (size_t i = 0; i < size; ++i) v[i] = dist(rng);
    return v;
}

string generateRandomString(size_t len = 8) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    uniform_int_distribution<int> dist(0, sizeof(charset) - 2);
    string s;
    s.reserve(len);
    for (size_t i = 0; i < len; ++i) s += charset[dist(rng)];
    return s;
}

vector<string> generateRandomStringVector(size_t size) {
    vector<string> v(size);
    for (size_t i = 0; i < size; ++i) v[i] = generateRandomString();
    return v;
}

template <typename T>
void printVector(const vector<T>& arr, size_t limit = 10) {
    cout << "[ ";
    for (size_t i = 0; i < min(arr.size(), limit); ++i) {
        cout << arr[i] << " ";
    }
    if (arr.size() > limit) cout << "... (" << arr.size() - limit << " elementos mas)";
    cout << "]\n";
}

// ANÁLISIS COMPARATIVO AUTOMÁTICO

template <typename T>
long long runSortTimed(int algoChoice, vector<T> data) {
    // Si es O(n^2) y tamaño >= 100,000, omitir o advertir debido al tiempo excesivo
    if ((algoChoice >= 1 && algoChoice <= 4) && data.size() > 50000) {
        return -1; // -1 indica que se omitió por costo computacional (>10 minutos)
    }
    Metrics m;
    switch (algoChoice) {
        case 1: m = swapSort(data); break;
        case 2: m = selectionSort(data); break;
        case 3: m = bubbleSort(data); break;
        case 4: m = insertionSort(data); break;
        case 5: m = mergeSort(data); break;
        case 6: m = quickSort(data); break;
        case 7: m = shellSort(data); break;
    }
    return m.duration_ns;
}

void runComparativeAnalysis() {
    cout << "\nGenerando analisis comparativo completo...\n";
    vector<string> algos = {"swapSort", "selectionSort", "bubbleSort", "insertionSort", "mergeSort", "quickSort", "shellSort"};
    vector<string> dataTypes = {"int", "double", "string"};

    cout << "\nalgoritmo, tipo_de_dato, tiempo1000, tiempo10000, tiempo100000 (en nanosegundos)\n";

    for (int a = 1; a <= 7; ++a) {
        for (const auto& dtype : dataTypes) {
            long long t1000 = 0, t10000 = 0, t100000 = 0;

            if (dtype == "int") {
                t1000 = runSortTimed(a, generateRandomInt(1000));
                t10000 = runSortTimed(a, generateRandomInt(10000));
                t100000 = runSortTimed(a, generateRandomInt(100000));
            } else if (dtype == "double") {
                t1000 = runSortTimed(a, generateRandomDouble(1000));
                t10000 = runSortTimed(a, generateRandomDouble(10000));
                t100000 = runSortTimed(a, generateRandomDouble(100000));
            } else {
                t1000 = runSortTimed(a, generateRandomStringVector(1000));
                t10000 = runSortTimed(a, generateRandomStringVector(10000));
                t100000 = runSortTimed(a, generateRandomStringVector(100000));
            }

            cout << algos[a - 1] << ", " << dtype << ", "
                 << (t1000 == -1 ? "OMITIDO" : to_string(t1000)) << ", "
                 << (t10000 == -1 ? "OMITIDO" : to_string(t10000)) << ", "
                 << (t100000 == -1 ? "OMITIDO" : to_string(t100000)) << "\n";
        }
    }
}

// INTERFAZ DE MENÚ PRINCIPAL

int main() {
    int option = -1;
    while (option != 0) {
        cout << "\n MENU PRINCIPAL\n";
        cout << "1. Ejecutar ordenamiento individual y ver metricas\n";
        cout << "2. Ejecutar analisis comparativo completo\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        if (!(cin >> option)) break;

        if (option == 1) {
            int typeChoice, sizeChoice, algoChoice;
            size_t n = 1000;

            cout << "\nSeleccione el tipo de dato:\n1. int\n2. double\n3. string\nOpcion: ";
            cin >> typeChoice;

            cout << "\nSeleccione la cantidad de datos:\n1. 1,000\n2. 10,000\n3. 100,000\nOpcion: ";
            cin >> sizeChoice;
            if (sizeChoice == 2) n = 10000;
            else if (sizeChoice == 3) n = 100000;

            cout << "\nSeleccione el algoritmo de ordenamiento:\n";
            cout << "1. Swap Sort\n2. Selection Sort\n3. Bubble Sort\n4. Insertion Sort\n";
            cout << "5. Merge Sort\n6. Quick Sort\n7. Shell Sort (No visto en clase)\nOpcion: ";
            cin >> algoChoice;

            Metrics m;
            if (typeChoice == 1) {
                vector<int> arr = generateRandomInt(n);
                switch (algoChoice) {
                    case 1: m = swapSort(arr); break;
                    case 2: m = selectionSort(arr); break;
                    case 3: m = bubbleSort(arr); break;
                    case 4: m = insertionSort(arr); break;
                    case 5: m = mergeSort(arr); break;
                    case 6: m = quickSort(arr); break;
                    case 7: m = shellSort(arr); break;
                }
                cout << "\nResultado de la lista ordenada:\n";
                printVector(arr);
            } else if (typeChoice == 2) {
                vector<double> arr = generateRandomDouble(n);
                switch (algoChoice) {
                    case 1: m = swapSort(arr); break;
                    case 2: m = selectionSort(arr); break;
                    case 3: m = bubbleSort(arr); break;
                    case 4: m = insertionSort(arr); break;
                    case 5: m = mergeSort(arr); break;
                    case 6: m = quickSort(arr); break;
                    case 7: m = shellSort(arr); break;
                }
                cout << "\nResultado de la lista ordenada:\n";
                printVector(arr);
            } else {
                vector<string> arr = generateRandomStringVector(n);
                switch (algoChoice) {
                    case 1: m = swapSort(arr); break;
                    case 2: m = selectionSort(arr); break;
                    case 3: m = bubbleSort(arr); break;
                    case 4: m = insertionSort(arr); break;
                    case 5: m = mergeSort(arr); break;
                    case 6: m = quickSort(arr); break;
                    case 7: m = shellSort(arr); break;
                }
                cout << "\nResultado de la lista ordenada:\n";
                printVector(arr);
            }


            cout << "\nMetricas de ejecucion:\n";
            cout << "Tiempo de ejecucion: " << m.duration_ns << " nanosegundos\n";
            if (algoChoice >= 1 && algoChoice <= 4) {
                cout << "Cantidad de comparaciones: " << m.comparisons << "\n";
                cout << "Cantidad de intercambios: " << m.swaps << "\n";
            }
        } else if (option == 2) {
            runComparativeAnalysis();
        }
    }
    return 0;
}