// ============================================
// ARCHIVO: Grafo.cxx
// ============================================
#include "Grafo.h"
#include <queue>
#include <cmath>
#include <algorithm>

double Grafo::calcularPeso(char base1, char base2) {
    int ascii1 = (int)base1;
    int ascii2 = (int)base2;
    return 1.0 / (1.0 + abs(ascii1 - ascii2));
}

void Grafo::construir(const Secuencia& sec) {
    nodos.clear();
    adyacencias.clear();
    posicionAIndice.clear();
    
    int filas = sec.obtenerFilas();
    int cols = sec.obtenerColumnas();
    
    // Crear nodos
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            if (sec.posicionValida(i, j)) {
                char base = sec.obtenerBase(i, j);
                int indice = nodos.size();
                nodos.push_back(Nodo(i, j, base));
                posicionAIndice[{i, j}] = indice;
            }
        }
    }
    
    adyacencias.resize(nodos.size());
    
    // Crear aristas (4 vecinos)
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    
    for (int idx = 0; idx < (int)nodos.size(); idx++) {
        int i = nodos[idx].fila;
        int j = nodos[idx].col;
        char base1 = nodos[idx].base;
        
        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            
            if (sec.posicionValida(ni, nj)) {
                auto it = posicionAIndice.find({ni, nj});
                if (it != posicionAIndice.end()) {
                    int vecino = it->second;
                    char base2 = nodos[vecino].base;
                    double peso = calcularPeso(base1, base2);
                    adyacencias[idx].push_back(Arista(vecino, peso));
                }
            }
        }
    }
}

std::vector<Nodo> Grafo::dijkstra(int origen, int destino, double& costoTotal) {
    int n = nodos.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> padre(n, -1);
    std::vector<bool> visitado(n, false);
    
    dist[origen] = 0;
    
    auto cmp = [&](int a, int b) { return dist[a] > dist[b]; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> pq(cmp);
    pq.push(origen);
    
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        
        if (visitado[u]) continue;
        visitado[u] = true;
        
        if (u == destino) break;
        
        for (const Arista& arista : adyacencias[u]) {
            int v = arista.destino;
            double peso = arista.peso;
            
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                padre[v] = u;
                pq.push(v);
            }
        }
    }
    
    std::vector<Nodo> camino;
    if (dist[destino] == std::numeric_limits<double>::infinity()) {
        costoTotal = -1;
        return camino;
    }
    
    costoTotal = dist[destino];
    int actual = destino;
    while (actual != -1) {
        camino.push_back(nodos[actual]);
        actual = padre[actual];
    }
    
    std::reverse(camino.begin(), camino.end());
    return camino;
}

int Grafo::obtenerIndice(int fila, int col) const {
    auto it = posicionAIndice.find({fila, col});
    if (it != posicionAIndice.end()) {
        return it->second;
    }
    return -1;
}

std::vector<int> Grafo::encontrarBasesIguales(char base) const {
    std::vector<int> indices;
    for (int i = 0; i < (int)nodos.size(); i++) {
        if (nodos[i].base == base) {
            indices.push_back(i);
        }
    }
    return indices;
}

Nodo Grafo::obtenerNodo(int indice) const {
    return nodos[indice];
}