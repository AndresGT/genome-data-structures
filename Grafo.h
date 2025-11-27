// ============================================
// ARCHIVO: Grafo.h
// ============================================
#ifndef GRAFO_H
#define GRAFO_H

#include "Secuencia.h"
#include <vector>
#include <map>
#include <utility>
#include <limits>

struct Nodo {
    int fila, col;
    char base;
    Nodo(int f, int c, char b) : fila(f), col(c), base(b) {}
};

struct Arista {
    int destino;
    double peso;
    Arista(int d, double p) : destino(d), peso(p) {}
};

class Grafo {
private:
    std::vector<Nodo> nodos;
    std::vector<std::vector<Arista>> adyacencias;
    std::map<std::pair<int,int>, int> posicionAIndice;
    
    double calcularPeso(char base1, char base2);

public:
    void construir(const Secuencia& sec);
    std::vector<Nodo> dijkstra(int origen, int destino, double& costoTotal);
    int obtenerIndice(int fila, int col) const;
    std::vector<int> encontrarBasesIguales(char base) const;
    Nodo obtenerNodo(int indice) const;
};

#endif