#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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

int main() {
    cout << "Prueba de Carga de Datos\n";
    
    // Probamos cargar el primer archivo desordenado
    string archivoPrueba = "log607-1.txt";
    vector<LogRecord> registros = cargarArchivo(archivoPrueba);
    
    if (!registros.empty()) {
        cout << "Se cargaron " << registros.size() << " lineas del archivo " << archivoPrueba << ".\n";
        cout << "\nComprobacion del primer registro leido:\n";
        cout << "Original: " << registros[0].lineaOriginal << "\n";
        cout << "Clave de ordenamiento generada: " << registros[0].claveOrdenamiento << "\n";
    }
    
    return 0;
}