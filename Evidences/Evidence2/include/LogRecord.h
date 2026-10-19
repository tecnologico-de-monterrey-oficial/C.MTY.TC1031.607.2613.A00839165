#ifndef LOGRECORD_H
#define LOGRECORD_H

#include <string>
#include <sstream>

using namespace std;

inline int mesAEntero(const string& m) {
    if (m == "Jan") return 1; if (m == "Feb") return 2;
    if (m == "Mar") return 3; if (m == "Apr") return 4;
    if (m == "May") return 5; if (m == "Jun") return 6;
    if (m == "Jul") return 7; if (m == "Aug") return 8;
    if (m == "Sep") return 9; if (m == "Oct") return 10;
    if (m == "Nov") return 11; if (m == "Dec") return 12;
    return 0;
}

struct LogRecord {
    string lineaOriginal;
    int mes, dia, anio;
    int hora, minuto, segundo;
    string ip, evento;

    // Sobrecarga del operador < para que funcione con Merge Sort
    bool operator<(const LogRecord& otro) const {
        if (anio != otro.anio) return anio < otro.anio;
        if (mes != otro.mes) return mes < otro.mes;
        if (dia != otro.dia) return dia < otro.dia;
        if (hora != otro.hora) return hora < otro.hora;
        if (minuto != otro.minuto) return minuto < otro.minuto;
        return segundo < otro.segundo;
    }
};

inline bool parsearLinea(const string& linea, LogRecord& registro) {
    stringstream ss(linea);
    string mesStr, tiempoStr, ip;
    int dia, anio;
    
    if (ss >> mesStr >> dia >> anio >> tiempoStr >> ip) {
        registro.lineaOriginal = linea;
        registro.mes = mesAEntero(mesStr);
        registro.dia = dia;
        registro.anio = anio;
        registro.ip = ip;
        
        if (tiempoStr.length() == 8 && tiempoStr[2] == ':' && tiempoStr[5] == ':') {
            registro.hora = stoi(tiempoStr.substr(0, 2));
            registro.minuto = stoi(tiempoStr.substr(3, 2));
            registro.segundo = stoi(tiempoStr.substr(6, 2));
        } else return false;

        getline(ss, registro.evento);
        if (!registro.evento.empty() && registro.evento[0] == ' ') {
            registro.evento = registro.evento.substr(1);
        }
        return registro.mes != 0;
    }
    return false;
}

#endif // LOGRECORD_H