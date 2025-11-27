// ============================================
// ARCHIVO: ArbolHuffman.h
// ============================================
#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "NodoHuffman.h"
#include <map>
#include <string>
#include <vector>

class ArbolHuffman {
private:
    NodoHuffman* raiz;
    std::map<char, std::string> codigos;
    
    void construirCodigos(NodoHuffman* nodo, const std::string& codigo);
    void decodificarRecursivo(NodoHuffman* nodo, const std::string& binario, 
                             int& pos, std::string& resultado);

public:
    ArbolHuffman();
    ~ArbolHuffman();
    
    void construir(const std::map<char, uint64_t>& frecuencias);
    std::string codificar(const std::string& texto);
    std::string decodificar(const std::string& binario);
    std::map<char, std::string> obtenerCodigos() const;
    std::map<char, uint64_t> obtenerFrecuencias() const;
};

#endif