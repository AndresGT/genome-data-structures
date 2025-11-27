// ============================================
// ARCHIVO: NodoHuffman.h
// ============================================
#ifndef NODOHUFFMAN_H
#define NODOHUFFMAN_H

#include <cstdint>

class NodoHuffman {
public:
    char simbolo;
    uint64_t frecuencia;
    NodoHuffman* izq;
    NodoHuffman* der;
    
    NodoHuffman(char s, uint64_t f);
    NodoHuffman(uint64_t f, NodoHuffman* izq, NodoHuffman* der);
    ~NodoHuffman();
    bool esHoja() const;
};

inline NodoHuffman::NodoHuffman(char s, uint64_t f) 
    : simbolo(s), frecuencia(f), izq(nullptr), der(nullptr) {}

inline NodoHuffman::NodoHuffman(uint64_t f, NodoHuffman* izq, NodoHuffman* der)
    : simbolo('\0'), frecuencia(f), izq(izq), der(der) {}

inline bool NodoHuffman::esHoja() const {
    return izq == nullptr && der == nullptr;
}

inline NodoHuffman::~NodoHuffman() {
    delete izq;
    delete der;
}

#endif