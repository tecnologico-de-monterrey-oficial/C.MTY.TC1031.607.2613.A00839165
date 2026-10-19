//A00839165   Julio Eduardo Rodriguez Ruiz

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

// Inclusión de los archivos header modulares
#include "../include/LogRecord.h"
#include "../include/Node.h"
#include "../include/Queue.h"
#include "../include/Stack.h"
#include "../include/DoubleLinkedList.h"

using namespace std;

int main() {
    cout << "Lector y Procesador de Logs de Red \n";
    cout << "Ingrese el nombre del archivo de bitacora (ej. log607-1.txt): ";
    string filename;
    getline(cin, filename);

    // Concatenamos "data/" al inicio del nombre del archivo
    string rutaCompleta = "../data/" + filename; 

    ifstream file(rutaCompleta);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo " << rutaCompleta << "\n";
        return 1;
    }

    Queue<string> filaLogs;
    string linea;
    while (getline(file, linea)) {
        if (!linea.empty()) filaLogs.enqueue(linea);
    }
    file.close();

    LogList listaLogs;
    int totalProcesados = 0;
    int omitidos = 0;
    int lineaActual = 1;

    while (!filaLogs.isEmpty()) {
        string logRaw = filaLogs.dequeue();
        LogRecord registro;
        if (parsearLinea(logRaw, registro)) {
            listaLogs.insertEnd(registro);
            totalProcesados++;
        } else {
            cout << "[Advertencia] Formato invalido omitido en la linea " << lineaActual << ": " << logRaw << "\n";
            omitidos++;
        }
        lineaActual++;
    }

    cout << "\nLectura completada. " << totalProcesados << " registros cargados. " << omitidos << " lineas omitidas.\n";
    
    int opcion = 0;
    bool ordenado = false;

    while (opcion != 5) {
        cout << "\nMenu Principal\n";
        cout << "1. Ordenar por fecha y hora\n";
        cout << "2. Buscar logs por dia\n";
        cout << "3. Mostrar logs por dia en orden descendente\n";
        cout << "4. Estadisticas del archivo\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();

        if (opcion == 1) {
            if (listaLogs.isSorted()) {
                cout << "\nEl archivo ya esta ordenado cronologicamente.\n";
                ordenado = true;
            } else {
                string prediccion;
                cout << "Ingrese su prediccion de crecimiento de comparaciones (ej. O(n log n)): ";
                getline(cin, prediccion);

                auto start = chrono::high_resolution_clock::now();
                listaLogs.sort();
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, std::milli> duration = end - start;

                ordenado = true;
                
                ofstream outFile("../out/output608.out");
                if (outFile.is_open()) {
                    DNode<LogRecord>* curr = listaLogs.head;
                    while (curr) {
                        outFile << curr->data.lineaOriginal << "\n";
                        curr = curr->next;
                    }
                    outFile.close();
                }

                cout << "\nResultados del Ordenamiento\n";
                cout << "Algoritmo: Merge Sort\n";
                cout << "Archivo procesado: " << filename << "\n";
                cout << "Tamano de datos: " << listaLogs.count << " registros\n";
                cout << "Tiempo de ejecucion: " << duration.count() << " ms\n";
                cout << "Comparaciones realizadas: " << listaLogs.comparaciones << "\n";
                cout << "Profundidad maxima de recursion: " << listaLogs.maxProfundidad << "\n";
                cout << "Prediccion del usuario: " << prediccion << "\n";
                cout << "Archivo de salida generado: output608.out\n";
            }
        } 
        else if (opcion == 2 || opcion == 3) {
            if (!ordenado) {
                cout << "\nAdvertencia: La lista debe ordenarse primero (Opcion 1) para un recorrido optimo.\n";
                continue;
            }

            cout << "Ingrese la fecha a buscar (Mes Dia Anio, ej. Sep 14 2024): ";
            string strBusqueda;
            getline(cin, strBusqueda);
            
            stringstream ssDate(strBusqueda);
            string mStr; int dBusqueda, yBusqueda;
            if (!(ssDate >> mStr >> dBusqueda >> yBusqueda)) {
                cout << "Formato de fecha invalido.\n";
                continue;
            }
            int mBusqueda = mesAEntero(mStr);
            if(mBusqueda == 0) {
                cout << "Mes invalido.\n";
                continue;
            }

            DNode<LogRecord>* curr = listaLogs.head;
            int encontrados = 0;
            Stack<LogRecord> pilaResultados;

            while (curr) {
                if (curr->data.anio > yBusqueda || 
                   (curr->data.anio == yBusqueda && curr->data.mes > mBusqueda) || 
                   (curr->data.anio == yBusqueda && curr->data.mes == mBusqueda && curr->data.dia > dBusqueda)) {
                    break;
                }
                
                if (curr->data.anio == yBusqueda && curr->data.mes == mBusqueda && curr->data.dia == dBusqueda) {
                    if (opcion == 2) cout << curr->data.lineaOriginal << "\n";
                    else pilaResultados.push(curr->data);
                    encontrados++;
                }
                curr = curr->next;
            }

            if (opcion == 3) {
                while (!pilaResultados.isEmpty()) {
                    cout << pilaResultados.pop().lineaOriginal << "\n";
                }
            }

            if (encontrados == 0) cout << "\nNo se encontraron registros para la fecha indicada.\n";
            else cout << "\nTotal de registros encontrados: " << encontrados << "\n";
        }
        else if (opcion == 4) {
            map<string, int> conteoDias;
            map<string, int> conteoEventos;
            map<string, int> conteoIPs;

            DNode<LogRecord>* curr = listaLogs.head;
            while (curr) {
                string diaLlave = to_string(curr->data.mes) + "/" + to_string(curr->data.dia) + "/" + to_string(curr->data.anio);
                conteoDias[diaLlave]++;
                conteoEventos[curr->data.evento]++;
                conteoIPs[curr->data.ip]++;
                curr = curr->next;
            }

            auto buscarMaximos = [](const map<string, int>& mapa, int& maxVal) {
                maxVal = 0;
                vector<string> maxLlaves;
                for (const auto& par : mapa) {
                    if (par.second > maxVal) {
                        maxVal = par.second;
                        maxLlaves.clear();
                        maxLlaves.push_back(par.first);
                    } else if (par.second == maxVal) {
                        maxLlaves.push_back(par.first);
                    }
                }
                return maxLlaves;
            };

            int maxDiasVal = 0, maxEvtVal = 0, maxIPVal = 0;
            vector<string> diasMasFrecuentes = buscarMaximos(conteoDias, maxDiasVal);
            vector<string> eventosMasFrecuentes = buscarMaximos(conteoEventos, maxEvtVal);
            vector<string> ipsMasFrecuentes = buscarMaximos(conteoIPs, maxIPVal);

            cout << "\n      Estadisticas del Archivo\n";
            cout << "Total de registros procesados: " << listaLogs.count << "\n";
            
            cout << "Dia(s) con mas incidentes (" << maxDiasVal << " apariciones):\n";
            for (const auto& d : diasMasFrecuentes) cout << "  - " << d << "\n";

            cout << "Evento(s) mas frecuente(s) (" << maxEvtVal << " apariciones):\n";
            for (const auto& e : eventosMasFrecuentes) cout << "  - " << e << "\n";

            cout << "IP(s) mas frecuente(s) (" << maxIPVal << " apariciones):\n";
            for (const auto& ip : ipsMasFrecuentes) cout << "  - " << ip << "\n";
        }
        else if (opcion != 5) {
            cout << "Opcion invalida, intente de nuevo.\n";
        }
    }
    
    cout << "Finalizado.\n";
    return 0;
}