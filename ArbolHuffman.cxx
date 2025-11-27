// ============================================
// ARCHIVO: ArbolHuffman.cxx
// ============================================
#include "ArbolHuffman.h"
#include <queue>
#include <algorithm>

struct CompararNodos {
    bool operator()(NodoHuffman* a, NodoHuffman* b) {
        return a->frecuencia > b->frecuencia;
    }
};

ArbolHuffman::ArbolHuffman() : raiz(nullptr) {}

ArbolHuffman::~ArbolHuffman() {
    delete raiz;
}

void ArbolHuffman::construir(const std::map<char, uint64_t>& frecuencias) {
    if (frecuencias.empty()) return;
    
    std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, CompararNodos> cola;
    
    for (auto& par : frecuencias) {
        cola.push(new NodoHuffman(par.first, par.second));
    }
    
    while (cola.size() > 1) {
        NodoHuffman* izq = cola.top(); cola.pop();
        NodoHuffman* der = cola.top(); cola.pop();
        
        NodoHuffman* padre = new NodoHuffman(izq->frecuencia + der->frecuencia, izq, der);
        cola.push(padre);
    }
    
    raiz = cola.top();
    codigos.clear();
    construirCodigos(raiz, "");
}

void ArbolHuffman::construirCodigos(NodoHuffman* nodo, const std::string& codigo) {
    if (!nodo) return;
    
    if (nodo->esHoja()) {
        codigos[nodo->simbolo] = codigo.empty() ? "0" : codigo;
    } else {
        construirCodigos(nodo->izq, codigo + "0");
        construirCodigos(nodo->der, codigo + "1");
    }
}

std::string ArbolHuffman::codificar(const std::string& texto) {
    std::string resultado;
    for (char c : texto) {
        resultado += codigos[c];
    }
    return resultado;
}

std::string ArbolHuffman::decodificar(const std::string& binario) {
    std::string resultado;
    int pos = 0;
    
    while (pos < (int)binario.length()) {
        NodoHuffman* actual = raiz;
        
        while (actual && !actual->esHoja() && pos < (int)binario.length()) {
            if (binario[pos] == '0') {
                actual = actual->izq;
            } else {
                actual = actual->der;
            }
            pos++;
        }
        
        if (actual && actual->esHoja()) {
            resultado += actual->simbolo;
        }
    }
    
    return resultado;
}

std::map<char, std::string> ArbolHuffman::obtenerCodigos() const {
    return codigos;
}

std::map<char, uint64_t> ArbolHuffman::obtenerFrecuencias() const {
    std::map<char, uint64_t> frecuencias;
    // Reconstruir frecuencias desde el árbol si es necesario
    return frecuencias;
}