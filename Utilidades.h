// ============================================
// ARCHIVO: Utilidades.h
// ============================================
#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "Secuencia.h"
#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

class Utilidades {
public:
    static bool cargarFASTA(const std::string& archivo, std::vector<Secuencia>& secuencias);
    static bool guardarFASTA(const std::string& archivo, const std::vector<Secuencia>& secuencias);
    static int contarSubsecuencias(const std::vector<Secuencia>& secuencias, const std::string& sub);
    static int enmascararSubsecuencias(std::vector<Secuencia>& secuencias, const std::string& sub);
    static std::map<char, uint64_t> calcularFrecuenciasGlobales(const std::vector<Secuencia>& secuencias);
    static bool codificarHuffman(const std::string& archivo, const std::vector<Secuencia>& secuencias);
    static bool decodificarHuffman(const std::string& archivo, std::vector<Secuencia>& secuencias);
private:
    static void escribirBits(std::ofstream& out, const std::string& bits, std::string& buffer);
    static void finalizarBuffer(std::ofstream& out, std::string& buffer);
    static std::string leerBits(std::ifstream& in, int numBits);
};

#endif
