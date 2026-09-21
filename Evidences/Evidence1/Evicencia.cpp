#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

// Estructura para representar un registro de la bitácora
struct LogRecord {
    string mes;
    int dia;
    int anio;
    string hora;
    string ip;
    string mensaje;
    string lineaOriginal;
    long long claveOrdenamiento;

    // Sobrecarga de operador para que los algoritmos puedan comparar registros fácilmente
    bool operator<(const LogRecord& otro) const {
        return claveOrdenamiento < otro.claveOrdenamiento;
    }
};

// Convierte el mes a su representación numérica
int mesANumero(const string& mes) {
    if (mes == "Jan") return 1; 
    if (mes == "Feb") return 2;
    if (mes == "Mar") return 3; 
    if (mes == "Apr") return 4;
    if (mes == "May") return 5; 
    if (mes == "Jun") return 6;
    if (mes == "Jul") return 7; 
    if (mes == "Aug") return 8;
    if (mes == "Sep") return 9; 
    if (mes == "Oct") return 10;
    if (mes == "Nov") return 11; 
    if (mes == "Dec") return 12;
    return 0;
}

// Genera una clave numérica AAAA MM DD HH MM SS para facilitar la comparación
long long generarClave(int anio, const string& mesStr, int dia, const string& horaStr) {
    int mes = mesANumero(mesStr);
    int h, m, s;
    char sep1, sep2; // Para atrapar los ':' en la hora
    stringstream ss(horaStr);
    ss >> h >> sep1 >> m >> sep2 >> s;
    
    // Construimos el número desplazando posiciones
    long long clave = anio;
    clave = clave * 100 + mes;
    clave = clave * 100 + dia;
    clave = clave * 100 + h;
    clave = clave * 100 + m;
    clave = clave * 100 + s;
    return clave;
}

// Carga los datos del archivo a un vector
vector<LogRecord> cargarArchivo(const string& nombreArchivo) {
    vector<LogRecord> registros;
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << "\n";
        return registros;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue; // Evita líneas en blanco
        stringstream ss(linea);
        LogRecord reg;
        // Leemos los primeros datos separados por espacios
        ss >> reg.mes >> reg.dia >> reg.anio >> reg.hora >> reg.ip;
        // El resto de la línea es el mensaje
        getline(ss, reg.mensaje);
        
        reg.lineaOriginal = linea;
        reg.claveOrdenamiento = generarClave(reg.anio, reg.mes, reg.dia, reg.hora);
        registros.push_back(reg);
    }
    archivo.close();
    return registros;
}

// Swap Sort (Intercambio directo ingenuo) - Complejidad O(n^2)
void swapSort(vector<LogRecord>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

// Bubble Sort - Complejidad O(n^2)
void bubbleSort(vector<LogRecord>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j + 1] < arr[j]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Algoritmo: Selection Sort - Complejidad O(n^2)
void selectionSort(vector<LogRecord>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

// Algoritmo: Insertion Sort - Complejidad O(n^2) peor caso, O(n) mejor caso
void insertionSort(vector<LogRecord>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        LogRecord key = arr[i];
        int j = i - 1;
        while (j >= 0 && key < arr[j]) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Auxiliar para Merge Sort: fusiona dos mitades ordenadas
void merge(vector<LogRecord>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<LogRecord> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        // Comparamos usando la sobrecarga del operador <
        if (!(R[j] < L[i])) { 
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
}

// Algoritmo 3: Merge Sort - Complejidad O(n log n)
void mergeSort(vector<LogRecord>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// Auxiliar para Quick Sort
int partition(vector<LogRecord>& arr, int low, int high) {
    LogRecord pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quick Sort - Complejidad O(n log n) promedio, O(n^2) peor caso
void quickSort(vector<LogRecord>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Búsqueda Binaria para el límite inferior (encuentra la primera aparición del rango)
int busquedaBinariaInicio(const vector<LogRecord>& arr, long long claveBuscada) {
    int inicio = 0, fin = arr.size() - 1;
    int resultado = -1;
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        // Si el valor medio es mayor o igual, es candidato a ser el inicio
        if (arr[medio].claveOrdenamiento >= claveBuscada) {
            resultado = medio;
            fin = medio - 1; 
        } else {
            inicio = medio + 1;
        }
    }
    return resultado;
}

// Búsqueda Binaria para el límite superior (encuentra la última aparición del rango)
int busquedaBinariaFin(const vector<LogRecord>& arr, long long claveBuscada) {
    int inicio = 0, fin = arr.size() - 1;
    int resultado = -1;
    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        // Si el valor medio es menor o igual, es candidato a ser el fin
        if (arr[medio].claveOrdenamiento <= claveBuscada) {
            resultado = medio;
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return resultado;
}

// Función para exportar un vector de registros a un archivo de texto
void guardarArchivo(const string& nombreArchivo, const vector<LogRecord>& registros) {
    ofstream archivo(nombreArchivo);
    for (const auto& reg : registros) {
        archivo << reg.lineaOriginal << "\n";
    }
    archivo.close();
}

int main() {
int opcionArchivo, opcionAlgoritmo;
    string prediccion;
    
    while (true) {
        cout << "\nSistema de Procesamiento de Logs\n";
        cout << "1. Usar log607-1.txt (Desordenado)\n";
        cout << "2. Usar log607-2.txt (Casi ordenado)\n";
        cout << "3. Salir\n";
        cout << "Elige una opcion: ";
        cin >> opcionArchivo;
        
        if (opcionArchivo == 3) break;
        
        string archivoEntrada = (opcionArchivo == 1) ? "log607-1.txt" : "log607-2.txt";
        vector<LogRecord> registros = cargarArchivo(archivoEntrada);
        
        if (registros.empty()) continue;
        
        cout << "\nAlgoritmos de Ordenamiento Disponibles:\n";
        cout << "1. Swap Sort\n";
        cout << "2. Bubble Sort\n";
        cout << "3. Selection Sort\n";
        cout << "4. Insertion Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Quick Sort\n";
        cout << "Elige un algoritmo: ";
        cin >> opcionAlgoritmo;
        
        cin.ignore();
        cout << "\nEscribe tu prediccion sobre el tiempo de ejecucion y por que:\n> ";
        getline(cin, prediccion);
        
        auto inicio = chrono::high_resolution_clock::now();
        string nombreAlgoritmo;
        
        switch (opcionAlgoritmo) {
            case 1:
                swapSort(registros);
                nombreAlgoritmo = "Swap Sort";
                break;
            case 2:
                bubbleSort(registros);
                nombreAlgoritmo = "Bubble Sort";
                break;
            case 3:
                selectionSort(registros);
                nombreAlgoritmo = "Selection Sort";
                break;
            case 4:
                insertionSort(registros);
                nombreAlgoritmo = "Insertion Sort";
                break;
            case 5:
                mergeSort(registros, 0, registros.size() - 1);
                nombreAlgoritmo = "Merge Sort";
                break;
            case 6:
                quickSort(registros, 0, registros.size() - 1);
                nombreAlgoritmo = "Quick Sort";
                break;
            default:
                cout << "Opcion no valida.\n";
                continue;
        }
        
        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> tiempo = fin - inicio;
        
        cout << "\nResultados de la Corrida\n";
        cout << "Algoritmo: " << nombreAlgoritmo << "\n";
        cout << "Archivo: " << archivoEntrada << " | Tamaño: " << registros.size() << " lineas\n";
        cout << "Tiempo de ejecucion: " << tiempo.count() << " ms\n";
        
        if (opcionAlgoritmo >= 1 && opcionAlgoritmo <= 3) {
            cout << "Complejidad Teorica: Peor caso O(n^2) | Mejor caso O(n^2)\n";
        } else if (opcionAlgoritmo == 4) {
            cout << "Complejidad Teorica: Peor caso O(n^2) | Mejor caso O(n)\n";
        } else if (opcionAlgoritmo == 5) {
            cout << "Complejidad Teorica: Peor caso O(n log n) | Mejor caso O(n log n)\n";
        } else if (opcionAlgoritmo == 6) {
            cout << "Complejidad Teorica: Peor caso O(n^2) | Mejor caso O(n log n)\n";
        }
        
        guardarArchivo("output607.txt", registros);
        cout << ">> Datos ordenados exportados a output607.txt correctamente.\n";
        
        cout << "\n Busqueda Binaria por Rango Temporal\n";
        cout << "Formato de busqueda (Mes Dia Ano Hora:Min:Seg) ej. Sep 12 2025 04:33:01\n";
        
        string m1, h1, m2, h2; 
        int d1, a1, d2, a2;
        
        cout << "Rango Inicio (Mes Dia Anio Hora): ";
        cin >> m1 >> d1 >> a1 >> h1;
        cout << "Rango Fin (Mes Dia Anio Hora): ";
        cin >> m2 >> d2 >> a2 >> h2;
        
        long long clave1 = generarClave(a1, m1, d1, h1);
        long long clave2 = generarClave(a2, m2, d2, h2);
        
        int idxInicio = busquedaBinariaInicio(registros, clave1);
        int idxFin = busquedaBinariaFin(registros, clave2);
        
        if (idxInicio != -1 && idxFin != -1 && idxInicio <= idxFin) {
            int totalEncontrados = idxFin - idxInicio + 1;
            cout << "\nSe encontraron " << totalEncontrados << " registros en el rango especificado.\n";
            vector<LogRecord> rangoRegistros(registros.begin() + idxInicio, registros.begin() + idxFin + 1);
            guardarArchivo("range607.txt", rangoRegistros);
            cout << ">> Registros de la busqueda guardados en range607.txt correctamente.\n";
        } else {
            cout << "\nNo se encontraron registros en el rango especificado.\n";
        }
    }
    
    return 0;
}