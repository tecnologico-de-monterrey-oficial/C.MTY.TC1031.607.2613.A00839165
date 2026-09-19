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
    
    // Construimos el número desplazando posiciones (ej. 20240929143738)
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

// Algoritmo 1: Selection Sort - Complejidad O(n^2)
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

// Algoritmo 2: Insertion Sort - Complejidad O(n^2) peor caso, O(n) mejor caso
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
