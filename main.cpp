
// ============================================
// ARCHIVO: main.cpp
// ============================================
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Secuencia.h"
#include "Utilidades.h"
#include "Grafo.h"
#include "Punto.h"

using namespace std;

vector<Secuencia> secuenciasEnMemoria;
map<string, Grafo> grafos;

void mostrarAyuda();
void mostrarAyudaComando(const string& comando);
void procesarComando(const string& linea);

// Comandos del Componente 1
void cmdCargar(const string& archivo);
void cmdListarSecuencias();
void cmdHistograma(const string& descripcion);
void cmdEsSubsecuencia(const string& subsecuencia);
void cmdEnmascarar(const string& subsecuencia);
void cmdGuardar(const string& archivo);

// Comandos del Componente 2
void cmdCodificar(const string& archivo);
void cmdDecodificar(const string& archivo);

// Comandos del Componente 3
void cmdRutaMasCorta(const string& descripcion, int i, int j, int x, int y);
void cmdBaseRemota(const string& descripcion, int i, int j);

int main() {
    string linea;
    
    cout << "Sistema de Manipulación de Genomas" << endl;
    cout << "Estructuras de Datos - Proyecto 2025-30" << endl;
    cout << "Escriba 'ayuda' para ver los comandos disponibles" << endl;
    cout << endl;
    
    while (true) {
        cout << "$ ";
        getline(cin, linea);
        
        if (linea.empty()) continue;
        procesarComando(linea);
    }
    
    return 0;
}

void procesarComando(const string& linea) {
    istringstream iss(linea);
    string comando;
    iss >> comando;
    
    if (comando == "salir") {
        exit(0);
    }
    else if (comando == "ayuda") {
        string subcomando;
        if (iss >> subcomando) {
            mostrarAyudaComando(subcomando);
        } else {
            mostrarAyuda();
        }
    }
    else if (comando == "cargar") {
        string archivo;
        if (iss >> archivo) {
            cmdCargar(archivo);
        } else {
            cout << "Error: debe especificar un nombre de archivo" << endl;
        }
    }
    else if (comando == "listar_secuencias") {
        cmdListarSecuencias();
    }
    else if (comando == "histograma") {
        string descripcion;
        getline(iss, descripcion);
        if (!descripcion.empty()) {
            descripcion = descripcion.substr(1);
            cmdHistograma(descripcion);
        } else {
            cout << "Error: debe especificar una descripción de secuencia" << endl;
        }
    }
    else if (comando == "es_subsecuencia") {
        string subsecuencia;
        if (iss >> subsecuencia) {
            cmdEsSubsecuencia(subsecuencia);
        } else {
            cout << "Error: debe especificar una subsecuencia" << endl;
        }
    }
    else if (comando == "enmascarar") {
        string subsecuencia;
        if (iss >> subsecuencia) {
            cmdEnmascarar(subsecuencia);
        } else {
            cout << "Error: debe especificar una subsecuencia" << endl;
        }
    }
    else if (comando == "guardar") {
        string archivo;
        if (iss >> archivo) {
            cmdGuardar(archivo);
        } else {
            cout << "Error: debe especificar un nombre de archivo" << endl;
        }
    }
    else if (comando == "codificar") {
        string archivo;
        if (iss >> archivo) {
            cmdCodificar(archivo);
        } else {
            cout << "Error: debe especificar un nombre de archivo" << endl;
        }
    }
    else if (comando == "decodificar") {
        string archivo;
        if (iss >> archivo) {
            cmdDecodificar(archivo);
        } else {
            cout << "Error: debe especificar un nombre de archivo" << endl;
        }
    }
    else if (comando == "ruta_mas_corta") {
        string descripcion;
        int i, j, x, y;
        if (iss >> descripcion >> i >> j >> x >> y) {
            cmdRutaMasCorta(descripcion, i, j, x, y);
        } else {
            cout << "Error: formato incorrecto. Uso: ruta_mas_corta descripcion i j x y" << endl;
        }
    }
    else if (comando == "base_remota") {
        string descripcion;
        int i, j;
        if (iss >> descripcion >> i >> j) {
            cmdBaseRemota(descripcion, i, j);
        } else {
            cout << "Error: formato incorrecto. Uso: base_remota descripcion i j" << endl;
        }
    }
    else {
        cout << "Comando no reconocido: " << comando << endl;
        cout << "Escriba 'ayuda' para ver los comandos disponibles" << endl;
    }
}

// ==================== COMPONENTE 1 ====================

void cmdCargar(const string& archivo) {
    if (Utilidades::cargarFASTA(archivo, secuenciasEnMemoria)) {
        grafos.clear();
        
        if (secuenciasEnMemoria.empty()) {
            cout << archivo << " no contiene ninguna secuencia." << endl;
        } else if (secuenciasEnMemoria.size() == 1) {
            cout << "1 secuencia cargada correctamente desde " << archivo << "." << endl;
        } else {
            cout << secuenciasEnMemoria.size() << " secuencias cargadas correctamente desde " 
                 << archivo << "." << endl;
        }
    } else {
        cout << archivo << " no se encuentra o no puede leerse." << endl;
    }
}

void cmdListarSecuencias() {
    if (secuenciasEnMemoria.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    
    cout << "Hay " << secuenciasEnMemoria.size() << " secuencias cargadas en memoria:" << endl;
    for (const auto& sec : secuenciasEnMemoria) {
        cout << "Secuencia " << sec.obtenerDescripcion();
        if (sec.esCompleta()) {
            cout << " contiene " << sec.obtenerNumBases() << " bases." << endl;
        } else {
            int bases = 0;
            for (char c : sec.obtenerDatos()) {
                if (c != '-') bases++;
            }
            cout << " contiene al menos " << bases << " bases." << endl;
        }
    }
}

void cmdHistograma(const string& descripcion) {
    bool encontrada = false;

    for (const auto& sec : secuenciasEnMemoria) {
        if (sec.obtenerDescripcion() == descripcion) {
            encontrada = true;

            auto histograma = sec.calcularHistograma();
            const char orden[] = "ACGTURYKMSWBDHVNX-";

            for (char c : orden) {
                if (histograma.count(c) > 0) {
                    cout << c << " : " << histograma.at(c) << endl;
                }
            }

            break;
        }
    }

    if (!encontrada) {
        cout << "Secuencia inválida." << endl;
    }
}


void cmdEsSubsecuencia(const string& subsecuencia) {
    if (secuenciasEnMemoria.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    
    int count = Utilidades::contarSubsecuencias(secuenciasEnMemoria, subsecuencia);
    
    if (count == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria." << endl;
    } else {
        cout << "La subsecuencia dada se repite " << count 
             << " veces dentro de las secuencias cargadas en memoria." << endl;
    }
}

void cmdEnmascarar(const string& subsecuencia) {
    if (secuenciasEnMemoria.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    
    int count = Utilidades::enmascararSubsecuencias(secuenciasEnMemoria, subsecuencia);
    grafos.clear();
    
    if (count == 0) {
        cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, "
             << "por tanto no se enmascara nada." << endl;
    } else {
        cout << count << " subsecuencias han sido enmascaradas dentro de las secuencias "
             << "cargadas en memoria." << endl;
    }
}

void cmdGuardar(const string& archivo) {
    if (secuenciasEnMemoria.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    
    if (Utilidades::guardarFASTA(archivo, secuenciasEnMemoria)) {
        cout << "Las secuencias han sido guardadas en " << archivo << "." << endl;
    } else {
        cout << "Error guardando en " << archivo << "." << endl;
    }
}

// ==================== COMPONENTE 2 ====================

void cmdCodificar(const string& archivo) {
    if (secuenciasEnMemoria.empty()) {
        cout << "No hay secuencias cargadas en memoria." << endl;
        return;
    }
    
    if (Utilidades::codificarHuffman(archivo, secuenciasEnMemoria)) {
        cout << "Secuencias codificadas y almacenadas en " << archivo << "." << endl;
    } else {
        cout << "No se pueden guardar las secuencias cargadas en " << archivo << "." << endl;
    }
}

void cmdDecodificar(const string& archivo) {
    if (Utilidades::decodificarHuffman(archivo, secuenciasEnMemoria)) {
        grafos.clear();
        cout << "Secuencias decodificadas desde " << archivo << " y cargadas en memoria." << endl;
    } else {
        cout << "No se pueden cargar las secuencias desde " << archivo << "." << endl;
    }
}

// ==================== COMPONENTE 3 ====================

void cmdRutaMasCorta(const string& descripcion, int i, int j, int x, int y) {
    Secuencia* secPtr = nullptr;
    
    for (auto& sec : secuenciasEnMemoria) {
        if (sec.obtenerDescripcion() == descripcion) {
            secPtr = &sec;
            break;
        }
    }
    
    if (!secPtr) {
        cout << "La secuencia " << descripcion << " no existe." << endl;
        return;
    }
    
    if (!secPtr->posicionValida(i, j)) {
        cout << "La base en la posición [" << i << "," << j << "] no existe." << endl;
        return;
    }
    
    if (!secPtr->posicionValida(x, y)) {
        cout << "La base en la posición [" << x << "," << y << "] no existe." << endl;
        return;
    }
    
    if (grafos.find(descripcion) == grafos.end()) {
        grafos[descripcion].construir(*secPtr);
    }
    
    Grafo& grafo = grafos[descripcion];
    int origen = grafo.obtenerIndice(i, j);
    int destino = grafo.obtenerIndice(x, y);
    
    double costo;
    vector<Nodo> camino = grafo.dijkstra(origen, destino, costo);
    
    char baseOrigen = secPtr->obtenerBase(i, j);
    char baseDestino = secPtr->obtenerBase(x, y);
    
    cout << "Para la secuencia " << descripcion << ", la ruta más corta entre "
         << "la base " << baseOrigen << " en [" << i << "," << j << "] y "
         << "la base " << baseDestino << " en [" << x << "," << y << "] es: ";
    
    for (size_t k = 0; k < camino.size(); k++) {
        cout << camino[k].base;
        if (k < camino.size() - 1) cout << " -> ";
    }
    
    cout << ". El costo total de la ruta es: " << fixed << setprecision(4) << costo << endl;
}

void cmdBaseRemota(const string& descripcion, int i, int j) {
    Secuencia* secPtr = nullptr;
    
    for (auto& sec : secuenciasEnMemoria) {
        if (sec.obtenerDescripcion() == descripcion) {
            secPtr = &sec;
            break;
        }
    }
    
    if (!secPtr) {
        cout << "La secuencia " << descripcion << " no existe." << endl;
        return;
    }
    
    if (!secPtr->posicionValida(i, j)) {
        cout << "La base en la posición [" << i << "," << j << "] no existe." << endl;
        return;
    }
    
    if (grafos.find(descripcion) == grafos.end()) {
        grafos[descripcion].construir(*secPtr);
    }
    
    Grafo& grafo = grafos[descripcion];
    int origen = grafo.obtenerIndice(i, j);
    char baseOrigen = secPtr->obtenerBase(i, j);
    
    vector<int> basesIguales = grafo.encontrarBasesIguales(baseOrigen);
    
    double maxCosto = -1;
    int mejorDestino = -1;
    vector<Nodo> mejorCamino;
    
    for (int destino : basesIguales) {
        if (destino == origen) continue;
        
        double costo;
        vector<Nodo> camino = grafo.dijkstra(origen, destino, costo);
        
        if (costo > maxCosto) {
            maxCosto = costo;
            mejorDestino = destino;
            mejorCamino = camino;
        }
    }
    
    if (mejorDestino == -1) {
        cout << "No hay bases remotas del mismo tipo." << endl;
        return;
    }
    
    Nodo nodoRemoto = grafo.obtenerNodo(mejorDestino);
    
    cout << "Para la secuencia " << descripcion << ", la base remota está ubicada "
         << "en [" << nodoRemoto.fila << "," << nodoRemoto.col << "], y la ruta entre "
         << "la base en [" << i << "," << j << "] y la base remota en ["
         << nodoRemoto.fila << "," << nodoRemoto.col << "] es: ";
    
    for (size_t k = 0; k < mejorCamino.size(); k++) {
        cout << mejorCamino[k].base;
        if (k < mejorCamino.size() - 1) cout << " -> ";
    }
    
    cout << ". El costo total de la ruta es: " << fixed << setprecision(4) 
         << maxCosto << endl;
}

// ==================== AYUDA ====================

void mostrarAyuda() {
    cout << "\n=== COMANDOS DISPONIBLES ===\n" << endl;
    cout << "COMPONENTE 1 - Estructuras Lineales:" << endl;
    cout << "  cargar <archivo>                  - Carga secuencias desde archivo FASTA" << endl;
    cout << "  listar_secuencias                 - Lista secuencias en memoria" << endl;
    cout << "  histograma <descripcion>          - Muestra histograma de secuencia" << endl;
    cout << "  es_subsecuencia <subsecuencia>    - Busca subsecuencia" << endl;
    cout << "  enmascarar <subsecuencia>         - Enmascara subsecuencia con X" << endl;
    cout << "  guardar <archivo>                 - Guarda secuencias en archivo" << endl;
    cout << "\nCOMPONENTE 2 - Árboles de Huffman:" << endl;
    cout << "  codificar <archivo.fabin>         - Codifica con Huffman" << endl;
    cout << "  decodificar <archivo.fabin>       - Decodifica desde binario" << endl;
    cout << "\nCOMPONENTE 3 - Grafos:" << endl;
    cout << "  ruta_mas_corta <desc> <i> <j> <x> <y> - Ruta más corta entre bases" << endl;
    cout << "  base_remota <desc> <i> <j>        - Encuentra base más lejana" << endl;
    cout << "\nGENERAL:" << endl;
    cout << "  ayuda [comando]                   - Ayuda general o específica" << endl;
    cout << "  salir                             - Termina el programa" << endl;
    cout << endl;
}

void mostrarAyudaComando(const string& comando) {
    if (comando == "cargar") {
        cout << "\nUSO: cargar <nombre_archivo>" << endl;
        cout << "Carga secuencias desde un archivo FASTA a memoria." << endl;
    }
    else if (comando == "listar_secuencias") {
        cout << "\nUSO: listar_secuencias" << endl;
        cout << "Lista todas las secuencias cargadas en memoria." << endl;
    }
    else if (comando == "histograma") {
        cout << "\nUSO: histograma <descripcion_secuencia>" << endl;
        cout << "Muestra frecuencia de cada base en la secuencia." << endl;
    }
    else if (comando == "es_subsecuencia") {
        cout << "\nUSO: es_subsecuencia <subsecuencia>" << endl;
        cout << "Cuenta ocurrencias de subsecuencia." << endl;
    }
    else if (comando == "enmascarar") {
        cout << "\nUSO: enmascarar <subsecuencia>" << endl;
        cout << "Reemplaza subsecuencias con X." << endl;
    }
    else if (comando == "guardar") {
        cout << "\nUSO: guardar <nombre_archivo>" << endl;
        cout << "Guarda secuencias en archivo FASTA." << endl;
    }
    else if (comando == "codificar") {
        cout << "\nUSO: codificar <archivo.fabin>" << endl;
        cout << "Codifica secuencias con Huffman." << endl;
    }
    else if (comando == "decodificar") {
        cout << "\nUSO: decodificar <archivo.fabin>" << endl;
        cout << "Decodifica desde archivo binario." << endl;
    }
    else if (comando == "ruta_mas_corta") {
        cout << "\nUSO: ruta_mas_corta <descripcion> <i> <j> <x> <y>" << endl;
        cout << "Calcula ruta más corta entre [i,j] y [x,y]." << endl;
    }
    else if (comando == "base_remota") {
        cout << "\nUSO: base_remota <descripcion> <i> <j>" << endl;
        cout << "Encuentra la misma base más lejana." << endl;
    }
    else {
        cout << "No hay ayuda para: " << comando << endl;
    }
}